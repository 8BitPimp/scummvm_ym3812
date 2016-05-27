/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include "titanic/true_talk/tt_parser.h"
#include "titanic/true_talk/script_handler.h"
#include "titanic/true_talk/tt_action.h"
#include "titanic/true_talk/tt_concept.h"
#include "titanic/true_talk/tt_sentence.h"
#include "titanic/true_talk/tt_word.h"
#include "titanic/titanic.h"

namespace Titanic {

TTparser::TTparser(CScriptHandler *owner) : _owner(owner), _sentenceConcept(nullptr),
		_sentence(nullptr), _fieldC(0), _field10(0), _field14(0),
		_currentWordP(nullptr), _nodesP(nullptr), _conceptP(nullptr) {
	loadArrays();
}

TTparser::~TTparser() {
	if (_nodesP) {
		_nodesP->deleteSiblings();
		delete _nodesP;
	}

	if (_conceptP) {
		_conceptP->deleteSiblings();
		delete _conceptP;
	}

	delete _currentWordP;
}

void TTparser::loadArray(StringArray &arr, const CString &name) {
	Common::SeekableReadStream *r = g_vm->_filesManager->getResource(name);
	while (r->pos() < r->size())
		arr.push_back(readStringFromStream(r));
	delete r;
}

void TTparser::loadArrays() {
	loadArray(_replacements1, "TEXT/REPLACEMENTS1");
	loadArray(_replacements2, "TEXT/REPLACEMENTS2");
	loadArray(_replacements3, "TEXT/REPLACEMENTS3");
	loadArray(_phrases, "TEXT/PHRASES");
	loadArray(_pronouns, "TEXT/PRONOUNS");

	Common::SeekableReadStream *r = g_vm->_filesManager->getResource("TEXT/NUMBERS");
	while (r->pos() < r->size()) {
		NumberEntry ne;
		ne._text = readStringFromStream(r);
		ne._value = r->readSint32LE();
		ne._flags = r->readUint32LE();
		_numbers.push_back(ne);
	}
	delete r;
}

int TTparser::preprocess(TTsentence *sentence) {
	_sentence = sentence;
	if (normalize(sentence))
		return 0;

	// Scan for and replace common slang and contractions with verbose versions
	searchAndReplace(sentence->_normalizedLine, _replacements1);
	searchAndReplace(sentence->_normalizedLine, _replacements2);

	// Check entire normalized line against common phrases to replace
	for (uint idx = 0; idx < _phrases.size(); idx += 2) {
		if (!_phrases[idx].compareTo(sentence->_normalizedLine))
			sentence->_normalizedLine = _phrases[idx + 1];
	}

	// Do a further search and replace of roman numerals to decimal
	searchAndReplace(sentence->_normalizedLine, _replacements3);

	// Replace any roman numerals, spelled out words, etc. with decimal numbers
	CTrueTalkManager::_v1 = -1000;
	int idx = 0;
	do {
		idx = replaceNumbers(sentence->_normalizedLine, idx);
	} while (idx >= 0);

	if (CTrueTalkManager::_v1 == -1000 && !sentence->_normalizedLine.empty()) {
		// Scan the text for any numeric digits
		for (const char *strP = sentence->_normalizedLine.c_str(); *strP; ++strP) {
			if (Common::isDigit(*strP)) {
				// Found digit, so convert it and any following ones
				CTrueTalkManager::_v1 = atoi(strP);
				break;
			}
		}
	}

	return 0;
}

int TTparser::normalize(TTsentence *sentence) {
	TTstring *destLine = new TTstring();
	const TTstring &srcLine = sentence->_initialLine;
	int srcSize = srcLine.size();
	int savedIndex = 0;
	int counter1 = 0;
	int commandVal;

	for (int index = 0; index < srcSize; ++index) {
		char c = srcLine[index];
		if (Common::isLower(c)) {
			(*destLine) += c;
		} else if (Common::isSpace(c)) {
			if (!destLine->empty() && destLine->lastChar() != ' ')
				(*destLine) += ' ';
		} else if (Common::isUpper(c)) {
			(*destLine) += toupper(c);
		} else if (Common::isDigit(c)) {
			if (c == '0' && isEmoticon(srcLine, index)) {
				sentence->set38(10);
			} else {
				// Iterate through all the digits of the number
				(*destLine) += c;
				while (Common::isDigit(srcLine[index + 1]))
					(*destLine) += srcLine[++index];
			}
		} else if (Common::isPunct(c)) {
			bool flag = false;
			switch (c) {
			case '!':
				sentence->set38(3);
				break;
			
			case '\'':
				if (!normalizeContraction(srcLine, index, *destLine))
					flag = true;
				break;
			
			case '.':
				sentence->set38(1);
				break;
			
			case ':':
				commandVal = isEmoticon(srcLine, index);
				if (commandVal) {
					sentence->set38(commandVal);
					index += 2;
				} else {
					flag = true;
				}
				break;
			
			case ';':
				commandVal = isEmoticon(srcLine, index);
				if (commandVal == 6) {
					sentence->set38(7);
					index += 2;
				} else if (commandVal != 0) {
					sentence->set38(commandVal);
					index += 2;
				}
				break;
			
			case '<':
				++index;
				commandVal = isEmoticon(srcLine, index);
				if (commandVal == 6) {
					sentence->set38(12);
				} else {
					--index;
					flag = true;
				}
				break;

			case '>':
				++index;
				commandVal = isEmoticon(srcLine, index);
				if (commandVal == 6 || commandVal == 9) {
					sentence->set38(11);
				} else {
					--index;
					flag = true;
				}
				break;

			case '?':
				sentence->set38(2);
				break;

			default:
				flag = true;
				break;
			}

			if (flag && (!savedIndex || (index - savedIndex) == 1))
				++counter1;

			savedIndex = index;
		}
	}

	if (counter1 >= 4)
		sentence->set38(4);

	// Remove any trailing spaces
	while (destLine->hasSuffix(" "))
		destLine->deleteLastChar();

	// Copy out the normalized line
	sentence->_normalizedLine = *destLine;
	delete destLine;

	return 0;
}

int TTparser::isEmoticon(const TTstring &str, int &index) {
	if (str[index] != ':' && str[index] != ';')
		return 0;

	if (str[index + 1] != '-')
		return 0;

	index += 2;
	switch (str[index]) {
	case '(':
	case '<':
		return 8;

	case ')':
	case '>':
		return 6;

	case 'P':
	case 'p':
		return 9;

	default:
		return 5;
	}
}

bool TTparser::normalizeContraction(const TTstring &srcLine, int srcIndex, TTstring &destLine) {
	int startIndex = srcIndex + 1;
	switch (srcLine[startIndex]) {
	case 'd':
		srcIndex += 2;
		if (srcLine.compareAt(srcIndex, " a ") || srcLine.compareAt(srcIndex, " the ")) {
			destLine += " had";
		} else {
			destLine += " would";
		}

		srcIndex = startIndex;
		break;

	case 'l':
		if (srcLine[srcIndex + 2] == 'l') {
			// 'll ending
			destLine += " will";
			srcIndex = startIndex;
		}
		break;

	case 'm':
		// 'm ending
		destLine += " am";
		srcIndex = startIndex;
		break;

	case 'r':
		// 're ending
		if (srcLine[srcIndex + 2] == 'e') {
			destLine += " are";
			srcIndex = startIndex;
		}
		break;

	case 's':
		destLine += "s*";
		srcIndex = startIndex;
		break;

	case 't':
		if (srcLine[srcIndex - 1] == 'n' && srcIndex >= 3) {
			if (srcLine[srcIndex - 3] == 'c' && srcLine[srcIndex - 2] == 'a' &&
				(srcIndex == 3 || srcLine[srcIndex - 4])) {
				// can't -> can not
				destLine += 'n';
			} else if (srcLine[srcIndex - 3] == 'w' && srcLine[srcIndex - 2] == 'o' &&
				(srcIndex == 3 || srcLine[srcIndex - 4])) {
				// won't -> will not
				destLine.deleteLastChar();
				destLine.deleteLastChar();
				destLine += "ill";
			} else if (srcLine[srcIndex - 3] == 'a' && srcLine[srcIndex - 2] == 'i' &&
				(srcIndex == 3 || srcLine[srcIndex - 4])) {
				// ain't -> am not
				destLine.deleteLastChar();
				destLine.deleteLastChar();
				destLine += "m";
			} else if (srcLine.hasSuffix(" sha") || 
					(srcIndex == 4 && srcLine.hasSuffix("sha"))) {
				// shan't -> shall not
				destLine.deleteLastChar();
				destLine += "ll";
			}

			destLine += " not";
		}
		break;

	case 'v':
		// 've ending
		if (srcLine[startIndex + 2] == 'e') {
			destLine += " have";
			srcIndex = startIndex;
		}
		break;

	default:
		break;
	}

	return false;
}

void TTparser::searchAndReplace(TTstring &line, const StringArray &strings) {
	int charIndex = 0;
	while (charIndex >= 0)
		charIndex = searchAndReplace(line, charIndex, strings);
}

int TTparser::searchAndReplace(TTstring &line, int startIndex, const StringArray &strings) {
	int lineSize = line.size();
	if (startIndex >= lineSize)
		return -1;

	for (uint idx = 0; idx < strings.size(); idx += 2) {
		const CString &origStr = strings[idx];
		const CString &replacementStr = strings[idx + 1];

		if (!strncmp(line.c_str() + startIndex, origStr.c_str(), strings[idx].size())) {
			// Ensure that that a space follows the match, or the end of string,
			// so the end of the string doesn't match on parts of larger words
			char c = line[startIndex + strings[idx].size()];
			if (c == ' ' || c == '\0') {
				// Replace the text in the line with it's replacement
				line = CString(line.c_str(), line.c_str() + startIndex) + replacementStr +
					CString(line.c_str() + startIndex + origStr.size());

				startIndex += replacementStr.size();
				break;
			}
		}
	}

	// Skip to the end of the current word
	while (startIndex < lineSize && line[startIndex] != ' ')
		++startIndex;
	if (startIndex == lineSize)
		return -1;

	// ..and all spaces following it until the start of the next word
	while (startIndex < lineSize && line[startIndex] == ' ')
		++startIndex;
	if (startIndex == lineSize)
		return -1;

	// Return index of the start of the next word
	return startIndex;
}

int TTparser::replaceNumbers(TTstring &line, int startIndex) {
	int index = startIndex;
	const NumberEntry *numEntry = replaceNumbers2(line, &index);
	if (!numEntry || !(numEntry->_flags & NF_2))
		return index;

	bool flag1 = false, flag2 = false, flag3 = false;
	int total = 0, factor = 0;

	do {
		if (numEntry->_flags & NF_1) {
			flag2 = true;
			if (numEntry->_flags & NF_8)
				flag1 = true;

			if (numEntry->_flags & NF_4) {
				flag3 = true;
				factor *= numEntry->_value;
			}

			if (numEntry->_flags & NF_2) {
				if (flag3) {
					total += factor;
					factor = 0;
				}

				factor += numEntry->_value;
			}
		}
	} while (replaceNumbers2(line, &index));

	if (!flag2)
		return index;

	if (index >= 0) {
		if (line[index - 1] != ' ')
			return index;
	}

	total += factor;
	CTrueTalkManager::_v1 = total;
	if (flag1)
		total = -total;

	CString numStr = CString::format("%d", total);
	line = CString(line.c_str(), line.c_str() + startIndex) + numStr +
		CString(line.c_str() + index);
	return index;
}

const NumberEntry *TTparser::replaceNumbers2(TTstring &line, int *startIndex) {
	int lineSize = line.size();
	int index = *startIndex;
	if (index < 0 || index >= lineSize) {
		*startIndex = -1;
		return nullptr;
	}

	NumberEntry *numEntry = nullptr;

	for (uint idx = 0; idx < _numbers.size(); ++idx) {
		NumberEntry &ne = _numbers[idx];
		if (!strncmp(line.c_str() + index, ne._text.c_str(), ne._text.size())) {
			if ((ne._flags & NF_10) || (index + (int)ne._text.size()) >= lineSize ||
					line[index + ne._text.size()] == ' ') {
				*startIndex += ne._text.size();
				numEntry = &ne;
				break;
			}
		}
	}

	if (!numEntry || !(numEntry->_flags & NF_10)) {
		// Skip to end of current word
		while (*startIndex < lineSize && !Common::isSpace(line[*startIndex]))
			++*startIndex;
	}

	// Skip over following spaces until start of following word is reached
	while (*startIndex < lineSize && Common::isSpace(line[*startIndex]))
		++*startIndex;

	if (*startIndex >= lineSize)
		*startIndex = -1;

	return numEntry;
}

int TTparser::findFrames(TTsentence *sentence) {
	static bool flag;
	_sentenceConcept = &sentence->_sentenceConcept;
	_sentence = sentence;

	TTstring *line = sentence->_normalizedLine.copy();
	TTstring wordString;
	int status = 0;
	for (int ctr = 1; !status; ++ctr) {
		// Keep stripping words off the start of the passed input
		wordString = line->tokenize(" \n");
		if (wordString.empty())
			break;

		TTword *srcWord = nullptr;
		TTword *word = _owner->_vocab->getWord(wordString, &word);
		sentence->storeVocabHit(srcWord);

		if (!word && ctr == 1) {
			word = new TTword(wordString, WC_UNKNOWN, 0);
		}

		for (TTword *currP = word; currP && !status; currP = currP->_nextP)
			status = processRequests(currP);

		word->deleteSiblings();
		delete word;
	}

	if (!status) {
		status = checkForAction();
	}

	delete line;
	return status;
}

int TTparser::loadRequests(TTword *word) {
	int status = 0;

	if (word->_tag != MKTAG('Z', 'Z', 'Z', 'T'))
		addNode(word->_tag);

	switch (word->_wordClass) {
	case WC_UNKNOWN:
		break;

	case WC_ACTION:
		if (word->_id != 0x70 && word->_id != 0x71)
			addNode(1);
		addNode(17);

		switch (word->_id) {
		case 101:
		case 110:
			addNode(5);
			addNode(4);
			break;

		case 102:
			addNode(4);
			break;

		case 103:
		case 111:
			addNode(8);
			addNode(7);
			addNode(5);
			addNode(4);
			break;

		case 104:
		case 107:
			addNode(15);
			addNode(5);
			addNode(4);
			break;

		case 106:
			addNode(7);
			addNode(4);
			break;

		case 108:
			addNode(5);
			addNode(4);
			addNode(23);
			break;

		case 112:
		case 113:
			addNode(13);
			addNode(5);
			break;

		default:
			break;
		}

		if (_sentenceConcept) {
			if (_sentenceConcept->get18() == 0 || _sentenceConcept->get18() == 2) {
				TTaction *action = static_cast<TTaction *>(word);
				_sentenceConcept->set18(action->getVal());
			}
		}
		break;

	case WC_THING:
		if (word->checkTag() && _sentence->_field58 > 0)
			_sentence->_field58--;
		addNode(14);
		break;

	case WC_ABSTRACT:
		switch (word->_id) {
		case 300:
			addNode(14);
			status = 1;
			break;

		case 306:
			addNode(23);
			addNode(4);
			break;

		case 307:
		case 308:
			addNode(23);
			break;

		default:
			break;
		}

		if (status != 1) {
			addToConceptList(word);
			addNode(14);
		}
		break;

	case WC_ARTICLE:
		addNode(2);
		status = 1;
		break;

	case WC_CONJUNCTION:
		if (_sentence->check2C()) {
			_sentenceConcept->_field1C = 1;
			_sentenceConcept = _sentenceConcept->addSibling();
			delete this;
		} else {
			addNode(23);
		}
		break;

	case WC_PRONOUN:
		status = fn2(word);
		break;

	case WC_PREPOSITION:
		switch (word->_id) {
		case 700:
			addNode(6);
			addNode(5);
			break;
		case 701:
			addNode(11);
			break;
		case 702:
			status = 1;
			break;
		case 703:
			addNode(9);
			break;
		case 704:
			addNode(10);
			break;
		default:
			break;
		}

	case WC_ADJECTIVE:
		if (word->_id == 304) {
			// Nothing
		} else if (word->_id == 801) {
			addNode(22);
		} else {
			if (word->proc16())
				_sentence->_field58++;
			if (word->proc17())
				_sentence->_field58++;
		}
		break;

	case WC_ADVERB:
		switch (word->_id) {
		case 900:
		case 901:
		case 902:
		case 904:
			if (_sentence->_field2C == 9) {
				_sentenceConcept->_field1C = 1;
				_sentenceConcept = _sentenceConcept->addSibling();
				addNode(1);
			}
			else {
				addNode(23);
				addNode(13);
				addNode(1);
			}
			break;

		case 905:
		case 907:
		case 908:
		case 909:
			addNode(23);
			break;

		case 906:
			addNode(23);
			status = 1;
			break;

		case 910:
			addNode(4);
			addNode(24);
			addNode(23);
			addNode(14);
			status = 1;
			break;

		default:
			break;
		}

		if (word->_id == 906) {
			addNode(14);
			status = 1;
		}
		break;

	default:
		break;
	}

	return status;
}

int TTparser::considerRequests(TTword *word) {
	if (_nodesP)
		return 0;

	TTparserNode *nodeP = _nodesP;
	TTconcept *concept = nullptr;
	int status = 0;
	bool flag = false;

	while (word) {
		//int ecx = 906;
		//int edx = 12;

		if (nodeP->_tag == MKTAG('C', 'O', 'M', 'E')) {
			addNode(7);
			addNode(5);
			addNode(21);

			if (!_sentence->_field2C)
				_sentence->_field2C = 15;
		} else if (nodeP->_tag == MKTAG('C', 'U', 'R', 'S') ||
				nodeP->_tag == MKTAG('S', 'E', 'X', 'X')) {
			if (_sentence->_field58 > 1)
				_sentence->_field58--;
			flag = true;

		} else if (nodeP->_tag == MKTAG('E', 'X', 'I', 'T')) {
			addNode(8);
			addNode(5);
			addNode(21);

			if (!_sentence->_field2C)
				_sentence->_field2C = 14;


		} else if (nodeP->_tag < MKTAG('C', 'O', 'M', 'E')) {
			if (_sentence->_field58 > 1)
				_sentence->_field58--;
			flag = true;
		} else {
			switch (nodeP->_tag) {
			case CHECK_COMMAND_FORM:
				if (_sentenceConcept->_concept1P && _sentence->_field2C == 1 &&
						!_sentenceConcept->_concept0P) {
					concept = new TTconcept(_sentence->_npcScript, ST_NPC_SCRIPT);
					_sentenceConcept->_concept0P = concept;
					_sentenceConcept->_field18 = 3;
				}

				flag = true;
				break;

			case EXPECT_THING:
				if (!word->_wordClass) {
					word->_wordClass = WC_THING;
					addToConceptList(word);
					addNode(14);
				}

				flag = true;
				break;

			case OBJECT_IS_TO:
				flag = resetConcept(&_sentenceConcept->_concept2P, 3);
				break;

			case SEEK_ACTOR:
				if (_sentenceConcept->_concept0P) {
					if (_sentenceConcept->_concept0P->compareTo("?") &&
							_sentenceConcept->_concept1P->isWordId(113) &&
							word->_wordClass == WC_THING) {
						// TODO
					}


				} else {

				}
				break;

			case SEEK_OBJECT:
			case SEEK_OBJECT_OVERRIDE:
			case SEEK_TO:
			case SEEK_FROM:
			case SEEK_TO_OVERRIDE:
			case SEEK_FROM_OVERRIDE:
				if (_sentenceConcept->_concept4P) {
					delete _sentenceConcept->_concept4P;
					_sentenceConcept->_concept4P = nullptr;
				}

				addNode(8);
				flag = true;
				break;

			case SEEK_LOCATION:
				addNode(5);
				_sentenceConcept->createConcept(0, 5, word);
				flag = true;
				break;

			case SEEK_OWNERSHIP:
			case SEEK_STATE:
			case SEEK_MODIFIERS:
			case SEEK_NEW_FRAME:
			case SEEK_STATE_OBJECT:
				if (!_sentenceConcept->_concept5P) {
					addToConceptList(word);
				} else if (_sentenceConcept->concept5WordId() == 113 ||
						_sentenceConcept->concept5WordId() == 112) {
					_sentenceConcept->createConcept(1, 2, word);
				} else {
					addToConceptList(word);
				}

				flag = true;
				break;

			case SET_ACTION:
				if (_sentence->fn4(1, 104, _sentenceConcept) ||
						_sentence->fn4(1, 107, _sentenceConcept)) {
					concept = _sentenceConcept->_concept1P;
					_sentenceConcept->_concept1P = nullptr;
					addNode(15);
				}

				if (_sentence->check2C() && word->_id == 113)
					addNode(4);

				if (word->_wordClass == WC_ACTION)
					_sentenceConcept->createConcept(0, 1, word);

				flag = true;
				break;

			case ACTOR_IS_TO:
				_sentenceConcept->changeConcept(1, &_sentenceConcept->_concept0P, 3);
				flag = true;
				break;

			case ACTOR_IS_FROM:
				_sentenceConcept->changeConcept(1, &_sentenceConcept->_concept0P, 4);
				break;

			case ACTOR_IS_OBJECT:
				flag = resetConcept(&_sentenceConcept->_concept0P, 2);
				break;

			case WORD_TYPE_IS_SENTENCE_TYPE:
			case COMPLEX_VERB:
				// TODO
				break;

			default:
				break;
			}
		}
	}

	// TODO
	delete concept;
	return status;
}

int TTparser::processRequests(TTword *word) {
	int status = loadRequests(word);
	switch (status) {
	case 0:
		status = considerRequests(word);
		
		// Iterate through the words
		while (_currentWordP) {
			considerRequests(_currentWordP);
			TTword *nextP = _currentWordP->_nextP;

			delete _currentWordP;
			_currentWordP = nextP;
		}
		break;

	case 1: {
		TTword *newWord = new TTword(word);
		newWord->_nextP = nullptr;

		// Add word to word chain
		if (_currentWordP) {
			// Add at end of existing chain
			for (word = _currentWordP; word->_nextP; word = word->_nextP)
				;
			word->_nextP = newWord;
		} else {
			// First word, so set as head
			_currentWordP = newWord;
		}
		break;
	}

	default:
		warning("unexpected return from consider requests");
		break;
	}

	return status;
}

void TTparser::addToConceptList(TTword *word) {
	TTconcept *concept = new TTconcept(word, ST_UNKNOWN_SCRIPT);
	addConcept(concept);
}

void TTparser::addNode(uint tag) {
	TTparserNode *newNode = new TTparserNode(tag);
	if (_nodesP)
		_nodesP->addToHead(newNode);
	_nodesP = newNode;
}

int TTparser::addConcept(TTconcept *concept) {
	if (!concept)
		return SS_5;

	if (_conceptP)
		concept->_nextP = _conceptP;
	_conceptP = concept;

	return SS_VALID;
}

void TTparser::removeConcept(TTconcept *concept) {
	// If no concept passed, exit immediately
	if (!concept)
		return;

	if (_conceptP == concept) {
		// Concept specified is the ver ystart of the linked list, so reset head pointer
		_conceptP = _conceptP->_nextP;
	} else {
		// Scan through the linked list, looking for the specific concept
		for (TTconcept *currP = _conceptP; currP; currP = currP->_nextP) {
			if (currP->_nextP == concept) {
				// Found match, so unlink the next link from the chain
				currP->_nextP = currP->_nextP->_nextP;
				break;
			}
		}
	}

	// FInally, delete the concept
	concept->_nextP = nullptr;
	delete concept;
}

void TTparser::removeNode(TTparserNode *node) {
	if (!node->_priorP)
		// Node is the head of the chain, so reset parser's nodes pointer
		_nodesP = static_cast<TTparserNode *>(node->_nextP);

	delete node;
}

int TTparser::checkForAction() {
	int status = SS_VALID;
	bool flag = false;
	bool actionFlag = false;

	if (_conceptP && _currentWordP) {
		// Firstly we need to get the next word to process, and remove it from
		// the list pointed to by _currentWordP
		TTword *word = _currentWordP;	
		if (word->_nextP) {
			// Chain of words, so we need to find the last word of the chain,
			// and set the last-but-one's _nextP to nullptr to detach the last one
			TTword *prior = nullptr;
			for (word = word->_nextP; word->_nextP; word = word->_nextP) {
				prior = word;
			}

			if (prior)
				prior->_nextP = nullptr;
		} else {
			// No chain, so singular word can simply be removed
			_currentWordP = nullptr;
			if (word->_id == 906 && _sentence->_field2C == 1)
				_sentence->_field2C = 12;
		}

		if (word->_text == "do" || word->_text == "doing" || word->_text == "does" ||
				word->_text == "done") {
			TTstring doStr("do");
			TTaction *action = new TTaction(doStr, WC_ACTION, 112, 0, _sentenceConcept->get18());
			
			if (!action->isValid()) {
				status = SS_4;
			} else {
				// Have the new action replace the old word instance
				delete word;
				word = action;
				actionFlag = true;
			}
		}

		addToConceptList(word);
		delete word;
		flag = true;
	}

	// Handle any remaining words
	TTword *reqWord = nullptr;
	while (_currentWordP) {
		if (considerRequests(_currentWordP) > 1) {
			reqWord = _currentWordP;
		} else {
			// Delete the top of the word chain
			TTword *wordP = _currentWordP;
			_currentWordP = _currentWordP->_nextP;
			delete wordP;
		}
	}

	if (flag && _conceptP) {
		if (actionFlag && (!_sentenceConcept->_concept1P || _sentenceConcept->_concept1P->isWordId(113))) {
			_sentenceConcept->replaceConcept(0, 1, _conceptP);
		} else if (!_sentenceConcept->_concept5P) {
			_sentenceConcept->replaceConcept(1, 5, _conceptP);
		} else if (_sentenceConcept->_concept5P->isWordId(904)) {
			_sentenceConcept->replaceConcept(0, 5, _conceptP);
		}

		removeConcept(_conceptP);
	}

	if (_sentence->fn2(3, TTstring("thePlayer"), _sentenceConcept) && !flag) {
		if (_sentenceConcept->concept1WordId() == 101) {
			_sentence->_field2C = 16;
		} else if (_sentence->_field2C != 18 && _sentenceConcept->concept1WordId() == 102) {
			if (_sentence->fn2(0, TTstring("targetNpc"), _sentenceConcept))
				_sentence->_field2C = 15;
		}
	}

	if (_sentence->fn2(2, TTstring("thePlayer"), _sentenceConcept) &&
			_sentenceConcept->concept1WordId() == 101 && flag)
		_sentence->_field2C = 17;

	if (!_sentenceConcept->_concept0P && !_sentenceConcept->_concept1P &&
			!_sentenceConcept->_concept2P && !_sentenceConcept->_concept5P && !flag) {
		if (_conceptP)
			filterConcepts(5, 2);

		if (!_sentenceConcept->_concept2P && _sentence->_field2C == 1)
			_sentence->_field2C = 0;
	}

	if (_sentence->_field58 < 5 && _sentence->_field2C == 1 && !flag)
		_sentence->_field2C = 19;

	for (TTconceptNode *nodeP = &_sentence->_sentenceConcept; nodeP; nodeP = nodeP->_nextP) {
		if (nodeP->_field18 == 0 && nodeP->_concept1P) {
			nodeP->_field18 = _sentence->concept18(nodeP);
		} else if (nodeP->_field18 == 4 && !_sentenceConcept->_concept0P) {
			if (_sentenceConcept->_concept3P) {
				_sentenceConcept->_concept0P = _sentenceConcept->_concept3P;
				_sentenceConcept->_concept3P = nullptr;
			} else if (_sentenceConcept->_concept2P) {
				_sentenceConcept->_concept0P = _sentenceConcept->_concept2P;
				_sentenceConcept->_concept2P = nullptr;
			}
		}
	}

	if (_sentence->_field2C == 1 && _sentenceConcept->_concept5P &&
			_sentenceConcept->_concept2P) {
		if (_sentence->fn4(1, 113, nullptr)) {
			if (_sentence->fn2(2, TTstring("targetNpc"), nullptr)) {
				_sentence->_field2C = 20;
			} else if (_sentence->fn2(2, TTstring("thePlayer"), nullptr)) {
				_sentence->_field2C = 21;
			} else {
				_sentence->_field2C = 22;
			}
		}
	} else if (!_sentenceConcept->_concept0P && !_sentenceConcept->_concept1P &&
			!_sentenceConcept->_concept2P && !_sentenceConcept->_concept5P) {
		if (_conceptP)
			filterConcepts(5, 2);

		if (!_sentenceConcept->_concept2P && _sentence->_field2C == 1)
			_sentence->_field2C = 0;
	}

	return status;
}

int TTparser::fn2(TTword *word) {
	switch (word->_id) {
	case 600:
		addNode(13);
		return 0;

	case 601:
		addNode(12);
		return 1;

	case 602:
	case 607:
		return checkReferent(static_cast<TTpronoun *>(word));

	case 608:
		return 1;

	default:
		return 0;
	}
}

int TTparser::checkReferent(TTpronoun *pronoun) {
	TTconcept *concept;

	switch (pronoun->getVal()) {
	case 0:
		return 0;

	case 1:
		concept = new TTconcept(_owner->_script, ST_ROOM_SCRIPT);
		break;

	case 2:
		concept = new TTconcept(_sentence->_npcScript, ST_NPC_SCRIPT);
		break;

	default:
		concept = new TTconcept(pronoun, (ScriptType)pronoun->getVal());
		break;
	}

	addConcept(concept);
	return 0;
}

void TTparser::conceptChanged(TTconcept *newConcept, TTconcept *oldConcept) {
	if (!oldConcept && newConcept != _currentConceptP)
		_currentConceptP = nullptr;
	else if (oldConcept && oldConcept == _currentConceptP)
		_currentConceptP = newConcept;
}

bool TTparser::checkConcept2(TTconcept *concept, int conceptMode) {
	switch (conceptMode) {
	case 3:
		return concept->checkWordId2();

	case 5:
		return concept->checkWordClass();

	case 8:
		return concept->checkWordId1();

	case 9:
		if (!concept->checkWordId3() && _sentenceConcept->_concept2P) {
			if (!_sentenceConcept->_concept2P->checkWordId2() || !concept->checkWordId2()) {
				return _sentenceConcept->_concept2P->checkWordClass() &&
					concept->checkWordClass();
			}
		}
		break;

	default:
		break;
	}

	return false;
}

int TTparser::filterConcepts(int conceptMode, int conceptIndex) {
	int result = 0;

	for (TTconcept *currP = _conceptP; currP && !result; currP = currP->_nextP) {
		if (checkConcept2(currP, conceptMode)) {
			TTconcept **ptrPP = _sentenceConcept->setConcept(conceptIndex, currP);
			TTconcept *newConcept = new TTconcept(*currP);
			*ptrPP = newConcept;

			if (newConcept->isValid()) {
				removeConcept(currP);
				(*ptrPP)->_nextP = nullptr;
				result = 1;
			} else {
				result = -2;
			}
		}
	}

	return result;
}

bool TTparser::resetConcept(TTconcept **conceptPP, int conceptIndex) {
	TTconcept **ptrPP = _sentenceConcept->setConcept(conceptIndex, nullptr);

	if (!*ptrPP)
		return 0;

	int result = _sentenceConcept->changeConcept(1, conceptPP, conceptIndex);
	if (*conceptPP)
		_sentenceConcept->setConcept(conceptIndex, *conceptPP);

	return !result;
}

} // End of namespace Titanic
