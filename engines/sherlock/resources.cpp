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

#include "sherlock/resources.h"
#include "sherlock/screen.h"
#include "sherlock/sherlock.h"
#include "common/debug.h"
#include "common/memstream.h"

namespace Sherlock {

Cache::Cache(SherlockEngine *vm) : _vm(vm) {
}

bool Cache::isCached(const Common::String &filename) const {
	return _resources.contains(filename);
}

void Cache::load(const Common::String &name) {
	// First check if the entry already exists
	if (_resources.contains(name))
		return;

	// Open the file for reading
	Common::File f;
	if (!f.open(name))
		error("Could not read file - %s", name.c_str());

	load(name, f);

	f.close();
}

void Cache::load(const Common::String &name, Common::SeekableReadStream &stream) {
	// First check if the entry already exists
	if (_resources.contains(name))
		return;

	int32 signature = stream.readUint32BE();
	stream.seek(0);

	// Allocate a new cache entry
	_resources[name] = CacheEntry();
	CacheEntry &cacheEntry = _resources[name];

	// Check whether the file is compressed
	if (signature == MKTAG('L', 'Z', 'V', 26)) {
		// It's compressed, so decompress the file and store it's data in the cache entry
		Common::SeekableReadStream *decompressed = _vm->_res->decompress(stream);
		cacheEntry.resize(decompressed->size());
		decompressed->read(&cacheEntry[0], decompressed->size());

		delete decompressed;
	} else {
		// It's not, so read the raw data of the file into the cache entry
		cacheEntry.resize(stream.size());
		stream.read(&cacheEntry[0], stream.size());
	}
}

Common::SeekableReadStream *Cache::get(const Common::String &filename) const {
	// Return a memory stream that encapsulates the data
	const CacheEntry &cacheEntry = _resources[filename];
	return new Common::MemoryReadStream(&cacheEntry[0], cacheEntry.size());
}

/*----------------------------------------------------------------*/

Resources::Resources(SherlockEngine *vm) : _vm(vm), _cache(vm) {
	_resourceIndex = -1;

	if (_vm->_interactiveFl) {
		if (_vm->getPlatform() != Common::kPlatform3DO) {
			addToCache("vgs.lib");
			addToCache("talk.lib");
			addToCache("journal.txt");

			if (IS_SERRATED_SCALPEL) {
				addToCache("sequence.txt");
				addToCache("portrait.lib");
			} else {
				addToCache("walk.lib");
			}
		} else {
			// 3DO

			// ITEM data from VGS.LIB is in ITEM.LIB
			// resources themselves start with width and height as UINT16BE
			// but after that they are different. Don't seem to be raw data
			//addToCache("item.lib");

			// talk.lib - resources themselves seem to be the same, although a few texts were slightly changed
			addToCache("talk.lib");

			// remaining files are missing
			// portraits were replaced with FMV
		}
	}
}

void Resources::addToCache(const Common::String &filename) {
	_cache.load(filename);

	// Check to see if the file is a library
	Common::SeekableReadStream *stream = load(filename);
	uint32 header = stream->readUint32BE();

	if (header == MKTAG('L', 'I', 'B', 26))
		loadLibraryIndex(filename, stream, false);
	else if (header == MKTAG('L', 'I', 'C', 26))
		loadLibraryIndex(filename, stream, true);

	delete stream;
}

void Resources::addToCache(const Common::String &filename, const Common::String &libFilename) {
	// Get the resource
	Common::SeekableReadStream *stream = load(filename, libFilename);

	_cache.load(filename, *stream);

	delete stream;
}

void Resources::addToCache(const Common::String &filename, Common::SeekableReadStream &stream) {
	_cache.load(filename, stream);
}

Common::SeekableReadStream *Resources::load(const Common::String &filename) {
	// First check if the file is directly in the cache
	if (_cache.isCached(filename))
		return _cache.get(filename);

	// Secondly, iterate through any loaded library file looking for a resource
	// that has the same name
	for (LibraryIndexes::iterator i = _indexes.begin(); i != _indexes.end(); ++i) {
		if (i->_value.contains(filename)) {
			// Get a stream reference to the given library file
			Common::SeekableReadStream *stream = load(i->_key);
			LibraryEntry &entry = i->_value[filename];
			_resourceIndex = entry._index;

			stream->seek(entry._offset);
			Common::SeekableReadStream *resStream = stream->readStream(entry._size);
			decompressIfNecessary(resStream);

			delete stream;
			return resStream;
		}
	}

	// At this point, fall back on a physical file with the given name
	Common::File f;
	if (!f.open(filename))
		error("Could not load file - %s", filename.c_str());

	Common::SeekableReadStream *stream = f.readStream(f.size());
	f.close();
	decompressIfNecessary(stream);

	return stream;
}

void Resources::decompressIfNecessary(Common::SeekableReadStream *&stream) {
	bool isCompressed = stream->readUint32BE() == MKTAG('L', 'Z', 'V', 26);

	if (isCompressed) {
		int outSize = stream->readUint32LE();
		Common::SeekableReadStream *newStream = decompressLZ(*stream, outSize);
		delete stream;
		stream = newStream;
	} else {
		stream->seek(-4, SEEK_CUR);
	}
}

Common::SeekableReadStream *Resources::load(const Common::String &filename, const Common::String &libraryFile) {
	// Open up the library for access
	Common::SeekableReadStream *libStream = load(libraryFile);

	// Check if the library has already had it's index read, and if not, load it
	if (!_indexes.contains(libraryFile))
		loadLibraryIndex(libraryFile, libStream, false);

	// Extract the data for the specified resource and return it
	LibraryEntry &entry = _indexes[libraryFile][filename];
	libStream->seek(entry._offset);
	Common::SeekableReadStream *stream = libStream->readStream(entry._size);
	decompressIfNecessary(stream);

	delete libStream;
	return stream;
}

bool Resources::exists(const Common::String &filename) const {
	Common::File f;
	return f.exists(filename) || _cache.isCached(filename);
}

void Resources::loadLibraryIndex(const Common::String &libFilename,
		Common::SeekableReadStream *stream, bool isNewStyle) {
	uint32 offset, nextOffset;

	// Create an index entry
	_indexes[libFilename] = LibraryIndex();
	LibraryIndex &index = _indexes[libFilename];

	// Read in the number of resources
	stream->seek(4);
	int count = 0;

	if (_vm->getPlatform() != Common::kPlatform3DO) {
		count = stream->readUint16LE();

		if (isNewStyle)
			stream->seek((count + 1) * 8, SEEK_CUR);

		// Loop through reading in the entries
		for (int idx = 0; idx < count; ++idx) {
			// Read the name of the resource
			char resName[13];
			stream->read(resName, 13);
			resName[12] = '\0';

			// Read the offset
			offset = stream->readUint32LE();

			if (idx == (count - 1)) {
				nextOffset = stream->size();
			} else {
				// Read the size by jumping forward to read the next entry's offset
				stream->seek(13, SEEK_CUR);
				nextOffset = stream->readUint32LE();
				stream->seek(-17, SEEK_CUR);
			}

			// Add the entry to the index
			index[resName] = LibraryEntry(idx, offset, nextOffset - offset);
		}

	} else {
		count = stream->readUint16BE();

		// 3DO header
		// Loop through reading in the entries
		for (int idx = 0; idx < count; ++idx) {
			// Read the offset
			offset = stream->readUint32BE();

			// Read the name of the resource
			char resName[13];
			stream->read(resName, 13);
			resName[12] = '\0';

			if (idx == (count - 1)) {
				nextOffset = stream->size();
			} else {
				// Read the size by jumping forward to read the next entry's offset
				stream->seek(13, SEEK_CUR);
				nextOffset = stream->readUint32BE();
				stream->seek(-17, SEEK_CUR);
			}

			// Add the entry to the index
			index[resName] = LibraryEntry(idx, offset, nextOffset - offset);
		}
	}
}

int Resources::resourceIndex() const {
	return _resourceIndex;
}

Common::SeekableReadStream *Resources::decompress(Common::SeekableReadStream &source) {
	// This variation can't be used by Rose Tattoo, since compressed resources include the input size,
	// not the output size. Which means their decompression has to be done via passed buffers
	assert(_vm->getGameID() == GType_SerratedScalpel);

	uint32 id = source.readUint32BE();
	assert(id == MKTAG('L', 'Z', 'V', 0x1A));

	uint32 outputSize = source.readUint32LE();
	return decompressLZ(source, outputSize);
}

Common::SeekableReadStream *Resources::decompress(Common::SeekableReadStream &source, uint32 outSize) {
	int inSize = (_vm->getGameID() == GType_RoseTattoo) ? source.readSint32LE() : -1;
	byte *outBuffer = (byte *)malloc(outSize);
	Common::MemoryReadStream *outStream = new Common::MemoryReadStream(outBuffer, outSize, DisposeAfterUse::YES);

	decompressLZ(source, outBuffer, outSize, inSize);

	return outStream;
}

void Resources::decompress(Common::SeekableReadStream &source, byte *buffer, uint32 outSize) {
	int inputSize = (_vm->getGameID() == GType_RoseTattoo) ? source.readSint32LE() : -1;

	decompressLZ(source, buffer, outSize, inputSize);
}

Common::SeekableReadStream *Resources::decompressLZ(Common::SeekableReadStream &source, uint32 outSize) {
	byte *dataOut = (byte *)malloc(outSize);
	decompressLZ(source, dataOut, outSize, -1);

	return new Common::MemoryReadStream(dataOut, outSize, DisposeAfterUse::YES);
}

void Resources::decompressLZ(Common::SeekableReadStream &source, byte *outBuffer, int32 outSize, int32 inSize) {
	byte lzWindow[4096];
	uint16 lzWindowPos;
	uint16 cmd;

	byte *outBufferEnd = outBuffer + outSize;
	int endPos = source.pos() + inSize;

	memset(lzWindow, 0xFF, 0xFEE);
	lzWindowPos = 0xFEE;
	cmd = 0;

	do {
		cmd >>= 1;
		if (!(cmd & 0x100))
			cmd = source.readByte() | 0xFF00;

		if (cmd & 1) {
			byte literal = source.readByte();
			*outBuffer++ = literal;
			lzWindow[lzWindowPos] = literal;
			lzWindowPos = (lzWindowPos + 1) & 0x0FFF;
		} else {
			int copyPos, copyLen;
			copyPos = source.readByte();
			copyLen = source.readByte();
			copyPos = copyPos | ((copyLen & 0xF0) << 4);
			copyLen = (copyLen & 0x0F) + 3;
			while (copyLen--) {
				byte literal = lzWindow[copyPos];
				copyPos = (copyPos + 1) & 0x0FFF;
				*outBuffer++ = literal;
				lzWindow[lzWindowPos] = literal;
				lzWindowPos = (lzWindowPos + 1) & 0x0FFF;
			}
		}
	} while ((outSize == -1 || outBuffer < outBufferEnd) && (inSize == -1 || source.pos() < endPos));
}

/*----------------------------------------------------------------*/

SherlockEngine *ImageFile::_vm;

void ImageFile::setVm(SherlockEngine *vm) {
	_vm = vm;
}

ImageFile::ImageFile(const Common::String &name, bool skipPal, bool animImages) {
	Common::SeekableReadStream *stream = _vm->_res->load(name);

	Common::fill(&_palette[0], &_palette[PALETTE_SIZE], 0);
	load(*stream, skipPal, animImages);

	delete stream;
}

ImageFile::ImageFile(Common::SeekableReadStream &stream, bool skipPal) {
	Common::fill(&_palette[0], &_palette[PALETTE_SIZE], 0);
	load(stream, skipPal, false);
}

ImageFile::~ImageFile() {
	for (uint idx = 0; idx < size(); ++idx)
		(*this)[idx]._frame.free();
}

void ImageFile::load(Common::SeekableReadStream &stream, bool skipPalette, bool animImages) {
	loadPalette(stream);

	int streamSize = stream.size();
	while (stream.pos() < streamSize) {
		ImageFrame frame;
		frame._width = stream.readUint16LE() + 1;
		frame._height = stream.readUint16LE() + 1;
		frame._paletteBase = stream.readByte();

		if (animImages) {
			// Animation cutscene image files use a 16-bit x offset
			frame._offset.x = stream.readUint16LE();
			frame._rleEncoded = (frame._offset.x & 0xff) == 1;
			frame._offset.y = stream.readByte();
		} else {
			// Standard image files have a separate byte for the RLE flag, and an 8-bit X offset
			frame._rleEncoded = stream.readByte() == 1;
			frame._offset.x = stream.readByte();
			frame._offset.y = stream.readByte();
		}

		frame._rleEncoded = !skipPalette && frame._rleEncoded;

		if (frame._paletteBase) {
			// Nibble packed frame data
			frame._size = (frame._width * frame._height) / 2;
		} else if (frame._rleEncoded) {
			// This size includes the header size, which we subtract
			frame._size = stream.readUint16LE() - 11;
			frame._rleMarker = stream.readByte();
		} else {
			// Uncompressed data
			frame._size = frame._width * frame._height;
		}

		// Load data for frame and decompress it
		byte *data = new byte[frame._size];
		stream.read(data, frame._size);
		decompressFrame(frame, data);
		delete[] data;

		push_back(frame);
	}
}

void ImageFile::loadPalette(Common::SeekableReadStream &stream) {
	// Check for palette
	int v1 = stream.readUint16LE() + 1;
	int v2 = stream.readUint16LE() + 1;
	stream.skip(1);		// Skip paletteBase byte
	bool rleEncoded = stream.readByte() == 1;
	int palSize = v1 * v2;

	if ((palSize - 12) == PALETTE_SIZE && !rleEncoded) {
		// Found palette, so read it in
		stream.seek(2 + 12, SEEK_CUR);
		for (int idx = 0; idx < PALETTE_SIZE; ++idx)
			_palette[idx] = VGA_COLOR_TRANS(stream.readByte());
	} else {
		// Not a palette, so rewind to start of frame data for normal frame processing
		stream.seek(-6, SEEK_CUR);
	}
}

void ImageFile::decompressFrame(ImageFrame &frame, const byte *src) {
	frame._frame.create(frame._width, frame._height, Graphics::PixelFormat::createFormatCLUT8());
	byte *dest = (byte *)frame._frame.getPixels();
	Common::fill(dest, dest + frame._width * frame._height, 0xff);

	if (frame._paletteBase) {
		// Nibble-packed
		for (uint idx = 0; idx < frame._size; ++idx, ++src) {
			*dest++ = *src & 0xF;
			*dest++ = (*src >> 4);
		}
	} else if (frame._rleEncoded && _vm->getGameID() == GType_RoseTattoo) {
		// Rose Tattoo run length encoding doesn't use the RLE marker byte
		for (int yp = 0; yp < frame._height; ++yp) {
			int xSize = frame._width;
			while (xSize > 0) {
				// Skip a given number of pixels
				byte skip = *src++;
				dest += skip;
				xSize -= skip;
				if (!xSize)
					break;

				// Get a run length, and copy the following number of pixels
				int rleCount = *src++;
				xSize -= rleCount;
				while (rleCount-- > 0)
					*dest++ = *src++;
			}
			assert(xSize == 0);
		}
	} else if (frame._rleEncoded) {
		// RLE encoded
		int frameSize = frame._width * frame._height;
		while (frameSize > 0) {
			if (*src == frame._rleMarker) {
				byte rleColor = src[1];
				byte rleCount = src[2];
				src += 3;
				frameSize -= rleCount;
				while (rleCount--)
					*dest++ = rleColor;
			} else {
				*dest++ = *src++;
				--frameSize;
			}
		}
		assert(frameSize == 0);
	} else {
		// Uncompressed frame
		Common::copy(src, src + frame._width * frame._height, dest);
	}
}

/*----------------------------------------------------------------*/

int ImageFrame::sDrawXSize(int scaleVal) const {
	int width = _width;
	int scale = scaleVal == 0 ? 1 : scaleVal;

	if (scaleVal >= SCALE_THRESHOLD)
		--width;

	int result = width * SCALE_THRESHOLD / scale;
	if (scaleVal >= SCALE_THRESHOLD)
		++result;

	return result;
}

int ImageFrame::sDrawYSize(int scaleVal) const {
	int height = _height;
	int scale = scaleVal == 0 ? 1 : scaleVal;

	if (scaleVal >= SCALE_THRESHOLD)
		--height;

	int result = height * SCALE_THRESHOLD / scale;
	if (scaleVal >= SCALE_THRESHOLD)
		++result;

	return result;
}

int ImageFrame::sDrawXOffset(int scaleVal) const {
	int width = _offset.x;
	int scale = scaleVal == 0 ? 1 : scaleVal;

	if (scaleVal >= SCALE_THRESHOLD)
		--width;

	int result = width * SCALE_THRESHOLD / scale;
	if (scaleVal >= SCALE_THRESHOLD)
		++result;

	return result;
}

int ImageFrame::sDrawYOffset(int scaleVal) const {
	int height = _offset.y;
	int scale = scaleVal == 0 ? 1 : scaleVal;

	if (scaleVal >= SCALE_THRESHOLD)
		--height;

	int result = height * SCALE_THRESHOLD / scale;
	if (scaleVal >= SCALE_THRESHOLD)
		++result;

	return result;
}

// *******************************************************

/*----------------------------------------------------------------*/

SherlockEngine *ImageFile3DO::_vm;

void ImageFile3DO::setVm(SherlockEngine *vm) {
	_vm = vm;
}

ImageFile3DO::ImageFile3DO(const Common::String &name, bool animImages) {
	Common::File *dataStream = new Common::File();

	if (!dataStream->open(name)) {
		error("unable to open %s\n", name.c_str());
	}

	load(*dataStream, animImages);

	delete dataStream;
}

ImageFile3DO::ImageFile3DO(Common::SeekableReadStream &stream) {
	load(stream, false);
}

ImageFile3DO::~ImageFile3DO() {
	for (uint idx = 0; idx < size(); ++idx)
		(*this)[idx]._frame.free();
}

void ImageFile3DO::load(Common::SeekableReadStream &stream, bool animImages) {
	uint32 headerId = stream.readUint32BE();

	assert(!stream.eos());

	// Seek back to the start
	stream.seek(-4, SEEK_CUR);

	// Identify type of file
	switch (headerId) {
	case MKTAG('C', 'C', 'B', ' '):
	case MKTAG('A', 'N', 'I', 'M'):
	case MKTAG('O', 'F', 'S', 'T'): // 3DOSplash.cel
		// 3DO .cel (title1a.cel, etc.) or animation file (walk.anim)
		load3DOCelFile(stream);
		break;

	default:
		// Sherlock animation file (.3da files)
		loadAnimationFile(stream, animImages);
		break;
	}
}

// 3DO uses RGB555, we use RGB565 internally so that more platforms are able to run us
inline uint16 ImageFile3DO::convertPixel(uint16 pixel3DO) {
	byte red   = (pixel3DO >> 10) & 0x1F;
	byte green = (pixel3DO >> 5) & 0x1F;
	byte blue  = pixel3DO & 0x1F;;

	return ((red << 11) | (green << 6) | (blue));
}

void ImageFile3DO::loadAnimationFile(Common::SeekableReadStream &stream, bool animImages) {
	int streamSize = stream.size();
	uint32 compressedSize = 0;

	while (stream.pos() < streamSize) {
		ImageFrame frame;

		compressedSize = stream.readUint16BE();

		frame._width = stream.readUint16BE() + 1; // 2 bytes BE width
		frame._height = stream.readByte() + 1; // 1 byte BE height
		frame._paletteBase = 0;

		if (animImages) {
			// Animation cutscene image files use a 16-bit x offset
			frame._offset.x = stream.readUint16BE();
			frame._rleEncoded = true; // always compressed
			if (frame._width & 0x8000) {
				frame._width &= 0x7FFF;
				compressedSize += 0x10000;
			}
			frame._offset.y = stream.readByte();
		} else {
			// Standard image files have a separate byte for the RLE flag, and an 8-bit X offset
			//frame._rleEncoded = stream.readByte() == 1;
			//frame._offset.x = stream.readByte();
			//frame._offset.y = stream.readByte();
		}

		frame._size = 0;

		//warning("getting frame %d from offset %d", this->size(), stream.pos());

		// Load data for frame and decompress it
		byte *data = new byte[compressedSize];
		stream.read(data, compressedSize);

		// always 16 bits per pixel (RGB555)
		decompress3DOCelFrame(frame, data, compressedSize, 16, NULL);

		delete[] data;

		push_back(frame);
	}
}

static byte imagefile3DO_cel_bitsPerPixelLookupTable[8] = {
	0, 1, 2, 4, 6, 8, 16, 0
};

// Reads a 3DO .cel/.anim file
void ImageFile3DO::load3DOCelFile(Common::SeekableReadStream &stream) {
	int32  chunkStartPos = 0;
	uint32 chunkTag = 0;
	uint32 chunkSize = 0;
	byte  *chunkDataPtr = NULL;

	ImageFrame imageFrame;

	// ANIM chunk (animation header for animation files)
	bool   animFound = false;
	uint32 animVersion = 0;
	uint32 animType = 0;
	uint32 animFrameCount = 1; // we expect 1 frame without an ANIM header
	// CCB chunk (cel control block)
	bool   ccbFound = false;
	uint32 ccbVersion = 0;
	uint32 ccbFlags = 0;
	bool   ccbFlags_compressed = false;
	uint16 ccbPPMP0 = 0;
	uint16 ccbPPMP1 = 0;
	uint32 ccbPRE0 = 0;
	byte   ccbPRE0_bitsPerPixel = 0;
	uint32 ccbPRE1 = 0;
	uint32 ccbWidth = 0;
	uint32 ccbHeight = 0;
	// pixel lookup table
	bool   plutFound = false;
	uint32 plutCount = 0;
	ImageFile3DOPixelLookupTable plutRGBlookupTable;

	memset(&plutRGBlookupTable, 0, sizeof(plutRGBlookupTable));

	while (!stream.err() && !stream.eos()) {
		chunkStartPos = stream.pos();
		chunkTag = stream.readUint32BE();
		chunkSize = stream.readUint32BE();

		if (chunkSize < 8)
			error("load3DOCelFile: Invalid chunk size");

		uint32 dataSize = chunkSize - 8;

		if (stream.eos() || stream.err())
			break;

		switch (chunkTag) {
		case MKTAG('A', 'N', 'I', 'M'):
			// animation header
			assert(dataSize >= 24);

			if (animFound)
				error("load3DOCelFile: multiple ANIM chunks not supported");

			animFound   = true;
			animVersion = stream.readUint32BE();
			animType = stream.readUint32BE();
			animFrameCount = stream.readUint32BE();
			// UINT32 - framerate (0x2000 in walk.anim???)
			// UINT32 - starting frame (0 for walk.anim)
			// UINT32 - number of loops (0 for walk.anim)

			if (animVersion != 0)
				error("load3DOCelFile: Unsupported animation file version");
			if (animType != 1)
				error("load3DOCelFile: Only single CCB animation files are supported");
			break;

		case MKTAG('C', 'C', 'B', ' '):
			// CEL control block
			assert(dataSize >= 72);

			if (ccbFound)
				error("load3DOCelFile: multiple CCB chunks not supported");

			ccbFound   = true;
			ccbVersion = stream.readUint32BE();
			ccbFlags   = stream.readUint32BE();
			stream.skip(3 * 4); // skip over 3 pointer fields, which are used in memory only by 3DO hardware
			stream.skip(8 * 4); // skip over 8 offset fields
			ccbPPMP0   = stream.readUint16BE();
			ccbPPMP1   = stream.readUint16BE();
			ccbPRE0    = stream.readUint32BE();
			ccbPRE1    = stream.readUint32BE();
			ccbWidth   = stream.readUint32BE();
			ccbHeight  = stream.readUint32BE();

			if (ccbVersion != 0)
				error("load3DOCelFile: Unsupported CCB version");

			if (ccbFlags & 0x200) // bit 9
				ccbFlags_compressed = true;

			// bit 5 of ccbFlags defines how RGB-black (0, 0, 0) will get treated
			// = false -> RGB-black is treated as transparent
			// = true  -> RGB-black is treated as actual black
			// atm we are always treating it as transparent
			// it seems this bit is not set for any data of Sherlock Holmes

			// PRE0 first 3 bits define how many bits per encoded pixel are used
			ccbPRE0_bitsPerPixel = imagefile3DO_cel_bitsPerPixelLookupTable[ccbPRE0 & 0x07];
			if (!ccbPRE0_bitsPerPixel)
				error("load3DOCelFile: Invalid CCB PRE0 bits per pixel");
			break;

		case MKTAG('P', 'L', 'U', 'T'):
			// pixel lookup table
			// optional, not required for at least 16-bit pixel data
			assert(dataSize >= 6);

			if (!ccbFound)
				error("load3DOCelFile: PLUT chunk found without CCB chunk");
			if (plutFound)
				error("load3DOCelFile: multiple PLUT chunks currently not supported");

			plutFound = true;
			plutCount = stream.readUint32BE();
			// table follows, each entry is 16bit RGB555
			assert(dataSize >= 4 + (plutCount * 2)); // security check
			assert(plutCount <= 256); // security check

			for (uint32 plutColor = 0; plutColor < plutCount; plutColor++) {
				plutRGBlookupTable.pixelColor[plutColor] = stream.readUint16BE();
			}
			break;

		case MKTAG('X', 'T', 'R', 'A'):
			// Unknown contents, occurs right before PDAT
			break;

		case MKTAG('P', 'D', 'A', 'T'):
			// pixel data for one frame
			// may be compressed or uncompressed pixels

			if (ccbPRE0_bitsPerPixel != 16) {
				// We require a pixel lookup table in case bits-per-pixel is lower than 16
				if (!plutFound)
					error("load3DOCelFile: bits per pixel < 16, but no pixel lookup table was found");
			} else {
				// But we don't like it in case bits-per-pixel is 16 and we find one
				if (plutFound)
					error("load3DOCelFile: bits per pixel == 16, but pixel lookup table was found as well");
			}
			// read data into memory
			chunkDataPtr = new byte[dataSize];

			stream.read(chunkDataPtr, dataSize);

			// Set up frame
			imageFrame._width = ccbWidth;
			imageFrame._height = ccbHeight;
			imageFrame._paletteBase = 0;
			imageFrame._offset.x = 0;
			imageFrame._offset.y = 0;
			imageFrame._rleEncoded = ccbFlags_compressed;
			imageFrame._size = 0;

			// Decompress/copy this frame
			if (!plutFound) {
				decompress3DOCelFrame(imageFrame, chunkDataPtr, dataSize, ccbPRE0_bitsPerPixel, NULL);
			} else {
				decompress3DOCelFrame(imageFrame, chunkDataPtr, dataSize, ccbPRE0_bitsPerPixel, &plutRGBlookupTable);
			}

			delete[] chunkDataPtr;

			push_back(imageFrame);
			break;

		case MKTAG('O', 'F', 'S', 'T'): // 3DOSplash.cel
			// unknown contents
			break;

		default:
			error("Unsupported '%s' chunk in 3DO cel file", tag2str(chunkTag));
		}

		// Seek to end of chunk
		stream.seek(chunkStartPos + chunkSize);
	}
}

static uint16 imagefile3DO_cel_bitsMask[17] = {
	0,
	0x0001, 0x0003, 0x0007, 0x000F, 0x001F, 0x003F, 0x007F, 0x00FF,
	0x01FF, 0x03FF, 0x07FF, 0x0FFF, 0x1FFF, 0x3FFF, 0x7FFF, 0xFFFF
};

// gets [bitCount] bits from dataPtr, going from MSB to LSB
inline uint16 ImageFile3DO::celGetBits(const byte *&dataPtr, byte bitCount, byte &dataBitsLeft) {
	byte   resultBitsLeft = bitCount;
	uint16 result = 0;
	byte   currentByte = *dataPtr;

	// Get bits of current byte
	while (resultBitsLeft) {
		if (resultBitsLeft < dataBitsLeft) {
			// we need less than we have left
			result |= (currentByte >> (dataBitsLeft - resultBitsLeft)) & imagefile3DO_cel_bitsMask[resultBitsLeft];
			dataBitsLeft -= resultBitsLeft;
			resultBitsLeft = 0;

		} else {
			// we need as much as we have left or more
			resultBitsLeft -= dataBitsLeft;
			result |= (currentByte & imagefile3DO_cel_bitsMask[dataBitsLeft]) << resultBitsLeft;

			// Go to next byte
			dataPtr++;
			currentByte = *dataPtr; dataBitsLeft = 8;
		}
	}
	return result;
}

// decompress/copy 3DO cel data
void ImageFile3DO::decompress3DOCelFrame(ImageFrame &frame, const byte *dataPtr, uint32 dataSize, byte bitsPerPixel, ImageFile3DOPixelLookupTable *pixelLookupTable) {
	frame._frame.create(frame._width, frame._height, Graphics::PixelFormat(2, 5, 6, 5, 0, 11, 5, 0, 0));
	uint16 *dest = (uint16 *)frame._frame.getPixels();
	Common::fill(dest, dest + frame._width * frame._height, 0);

	int frameHeightLeft = frame._height;
	int frameWidthLeft = frame._width;
	uint16 pixelCount = 0;
	uint16 pixel = 0;

	const  byte *srcLineStart = dataPtr;
	const  byte *srcLineData = dataPtr;
	byte   srcLineDataBitsLeft = 0;
	uint16 lineDWordSize = 0;
	uint16 lineByteSize = 0;

	if (bitsPerPixel == 16) {
		// Must not use pixel lookup table on 16-bits-per-pixel data
		assert(!pixelLookupTable);
	}

	if (frame._rleEncoded) {
		// compressed
		byte   compressionType = 0;
		byte   compressionPixels = 0;

		while (frameHeightLeft > 0) {
			frameWidthLeft = frame._width;

			if (bitsPerPixel >= 8) {
				lineDWordSize = READ_BE_UINT16(srcLineStart);
				srcLineData = srcLineStart + 2;
			} else {
				lineDWordSize = *srcLineStart;
				srcLineData = srcLineStart + 1;
			}
			srcLineDataBitsLeft = 8;

			lineDWordSize += 2;
			lineByteSize = lineDWordSize * 4; // calculate compressed data size in bytes for current line

			// debug
			//warning("offset %d: decoding line, size %d, bytesize %d", srcSeeker - src, dwordSize, lineByteSize);

			while (frameWidthLeft > 0) {
				// get 2 bits -> compressionType
				// get 6 bits -> pixel count (0 = 1 pixel)
				compressionType = celGetBits(srcLineData, 2, srcLineDataBitsLeft);
				// 6 bits == length (0 = 1 pixel)
				compressionPixels = celGetBits(srcLineData, 6, srcLineDataBitsLeft) + 1;

				if (!compressionType) // end of line
					break;

				switch(compressionType) {
				case 1: // simple copy
					for (pixelCount = 0; pixelCount < compressionPixels; pixelCount++) {
						pixel = celGetBits(srcLineData, bitsPerPixel, srcLineDataBitsLeft);
						if (pixelLookupTable) {
							pixel = pixelLookupTable->pixelColor[pixel];
						}
						*dest++ = convertPixel(pixel);
					}
					break;
				case 2: // transparent
					for (pixelCount = 0; pixelCount < compressionPixels; pixelCount++) {
						*dest++ = 0;
					}
					break;
				case 3: // duplicate pixels
					pixel = celGetBits(srcLineData, bitsPerPixel, srcLineDataBitsLeft);
					if (pixelLookupTable) {
						pixel = pixelLookupTable->pixelColor[pixel];
					}
					pixel = convertPixel(pixel);
					for (pixelCount = 0; pixelCount < compressionPixels; pixelCount++) {
						*dest++ = pixel;
					}
					break;
				default:
					break;
				}
				frameWidthLeft -= compressionPixels;
			}

			assert(frameWidthLeft >= 0);

			if (frameWidthLeft > 0) {
				// still pixels left? skip them
				dest += frameWidthLeft;
			}

			frameHeightLeft--;

			// Seek to next line start
			srcLineStart += lineByteSize;
		}
	} else {
		// uncompressed
		srcLineDataBitsLeft = 8;
		lineDWordSize = ((frame._width * bitsPerPixel) + 31) >> 5;
		lineByteSize = lineDWordSize * 4;
		uint32 totalExpectedSize = lineByteSize * frame._height;

		assert(totalExpectedSize <= dataSize); // security check

		while (frameHeightLeft > 0) {
			srcLineData = srcLineStart;
			frameWidthLeft = frame._width;

			while (frameWidthLeft > 0) {
				pixel = celGetBits(srcLineData, bitsPerPixel, srcLineDataBitsLeft);
				if (pixelLookupTable) {
					pixel = pixelLookupTable->pixelColor[pixel];
				}
				*dest++ = convertPixel(pixel);

				frameWidthLeft--;
			}
			frameHeightLeft--;

			// Seek to next line start
			srcLineStart += lineByteSize;
		}
	}
}

} // End of namespace Sherlock