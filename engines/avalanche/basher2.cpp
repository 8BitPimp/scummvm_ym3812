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

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

/*
 * This code is based on the original source code of Lord Avalot d'Argent version 1.3.
 * Copyright (c) 1994-1995 Mike, Mark and Thomas Thurman.
 */

/* BASHER		Handles the keyboard. */

// Note: this unit can record keystrokes, for the demo. If you want it
// to do this, define the o.c.c. RECORD. Setting gyro.demo to True will
// cause them to be played back. 

#include "avalanche/avalanche.h"

#include "avalanche/basher2.h"
#include "avalanche/enhanced2.h"
#include "avalanche/lucerna2.h"
#include "avalanche/scrolls2.h"
#include "avalanche/acci2.h"
#include "avalanche/trip6.h"
#include "avalanche/pingo2.h"
#include "avalanche/dropdown2.h"
#include "avalanche/logger2.h"
#include "avalanche/enid2.h"
//#include "Sticks.h" - Responsible for the joystick

#include "common/textconsole.h"

namespace Avalanche {
	
Basher::Basher() {
	warning("STUB: Basher::Basher()");
}

void Basher::setParent(AvalancheEngine *vm) {
	_vm = vm;
}

void Basher::plottext() {
	warning("STUB: Basher::plottext()");
}

void Basher::wipetext() {
	warning("STUB: Basher::wipetext()");
}

/*procedure cursor;
begin
 if curflash=0 then
 begin
  if mouse_near_text then Super_Off;
  cursoron:=not cursoron;
  mem[$A000*13442+curpos]:=not mem[$A000*13442+curpos];
  mem[$A000*pagetop+13442+curpos]:=not mem[$A000*pagetop+13442+curpos];
  curflash:=17;
  Super_On;
 end else dec(curflash);
end;*/

void Basher::do_cursor() {
	warning("STUB: Basher::do_cursor()");
}

void Basher::cursor_on() {
	warning("STUB: Basher::cursor_on()");
}

void Basher::cursor_off() {
	warning("STUB: Basher::cursor_off()");
}


void Basher::get_demorec() {
	warning("STUB: Basher::get_demorec()");
}

#ifdef RECORD
void Basher::record_one() {
	warning("STUB: Basher::record_one()");
}
#endif
/*
procedure storeline(whatwhat:string);
var
 fv:byte;
 what:string[77];
 ok:boolean;

  function upline(x:string):string;
  var fv:byte; n:string[77];
  begin
   for fv:=1 to length(x) do n[fv]:=upcase(x[fv]);
   n[0]:=x[0]; upline:=n;
  end;
begin

 what:=upline(whatwhat); ok:=false;
 for fv:=1 to 20 do
  if what=upline(previous^[fv]) then
  begin { it already exists, in string "fv" }
   move(previous^[fv+1],previous^[fv],(20-fv)*78);
   previous^[20]:=whatwhat; ok:=true;
  end;
 if ok then exit;
 { it's not on the list, so add it }
 move(previous^[2],previous^[1],1482); { shove up }
 previous^[20]:=whatwhat;
end;
*/


char Basher::firstchar(Common::String x) {
	warning("STUB: Basher::firstchar()");
	return 'S';
}


void Basher::try_dd() { /* This asks the Parsekey proc in Dropdown if it knows it. */
	warning("STUB: Basher::try_dd()");
}

void Basher::typein() {
	warning("STUB: Basher::typein()");
}

/*        'x'..'z': begin setvisualpage(ord(extd)-63); write(#7); inkey; end;
        '�': begin setvisualpage(0); write(#7); inkey; end;*/

void Basher::keyboard_link() {
	warning("STUB: Basher::keyboard_link()");
}

bool Basher::demo_ready() {
	warning("STUB: Basher::demo_ready()");
	return true;
}

void Basher::filename_edit() {
	warning("STUB: Basher::filename_edit()");
}

void Basher::normal_edit() {
	warning("STUB: Basher::normal_edit()");
}

} // End of namespace Avalanche.
