/* ScummVM - Scumm Interpreter
 * Copyright (C) 2003 The ScummVM project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Header$
 *
 */

#ifndef SKYMAIN_H
#define SKYMAIN_H

#include <stdio.h>
#include "common/engine.h"
#include "common/util.h"
#include "common/timer.h"
#include "sound/mixer.h"
#include "sky/sound.h"
#include "sky/text.h"
#include "sky/disk.h"
#include "sky/struc.h"
#include "sky/grid.h"
#include "sky/screen.h"
#include "sky/music/musicbase.h"
#include "sky/music/adlibmusic.h"
#include "sky/music/gmmusic.h"
#include "sky/music/mt32music.h"
#include "sky/mouse.h"

struct SystemVars {
	uint32 systemFlags;
	uint32 gameVersion;
	uint32 mouseFlag;
	uint16 language;
	/* uint16 sfxVolume;
	uint16 musicVolume;
	uint16 gameSpeed; */
};

class SkyLogic;
class SkyGrid;
class SkyAutoRoute;
class SkyScreen;

class SkyState : public Engine {
	void errorString(const char *buf_input, char *buf_output);
protected:
	byte _game;
	byte _key_pressed;

	//intro related
	
	byte *_introTextSpace;
	byte *_introTextSave;

	uint16 _debugMode;
	uint16 _debugLevel;
	uint _mouse_x, _mouse_y;
	uint _mouse_x_old, _mouse_y_old;
	bool _mouse_pos_changed;
	uint _left_button_down;

	int _numScreenUpdates;

	Timer *_timer;
	//int _timer_id;

	FILE *_dump_file;

	int _number_of_savegames;

	int _sdl_mouse_x, _sdl_mouse_y;

	SkySound *_skySound;
	SkyDisk *_skyDisk;
	SkyText *_skyText;
	SkyGrid *_skyGrid;
	SkyLogic *_skyLogic;
	SkyMouse *_skyMouse;
	SkyScreen *_skyScreen;

	SkyMusicBase *_skyMusic;
	GameDetector *_detector; // necessary for music
	
public:
	SkyState(GameDetector *detector, OSystem *syst);
	virtual ~SkyState();

	static bool isDemo(void);
	static bool isCDVersion(void);

	static Compact *fetchCompact(uint32 a);
	static void **fetchItem(uint32 num);
	
	static void **_itemList[300];

	static SystemVars _systemVars;

	//intro related
	void prepareText(uint32 *&cmdPtr);
	void showIntroText(uint32 *&cmdPtr);
	void removeText(uint32 *&cmdPtr);
	void introFx(uint32 *&cmdPtr);
	void introVol(uint32 *&cmdPtr); 


protected:
	void logic_engine();
	void delay(uint amount);
	void pollMouseXY();
	void go();

	//intro related
	static uint8 fosterImg[297 * 143];
	static uint8 fosterPal[256 * 3];
	void checkCommands(uint32 *&cmdPtr);
	void introFrame(uint8 **diffPtr, uint8 **vgaPtr, uint8 *screenData);

	SkyText *getSkyText();
	void initialise();
	void initItemList();

	void initVirgin();
	void intro();
	void doCDIntro();
	void startTimerSequence(byte *sequence);
	static void timerHandler(void *ptr);
	void gotTimerTick();
	void loadFixedItems();
	void loadBase0();
	
	static int CDECL game_thread_proc(void *param);

	void shutdown();

	void showQuitMsg(void);

	RandomSource _rnd;
};

#endif
