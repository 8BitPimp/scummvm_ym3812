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

#include "common/scummsys.h"

#include "zvision/actions.h"
#include "zvision/zvision.h"
#include "zvision/script_manager.h"
#include "zvision/action_node.h"

namespace ZVision {

//////////////////////////////////////////////////////////////////////////////
// ActionAdd
//////////////////////////////////////////////////////////////////////////////

	sscanf(line->c_str(), ":add(%u,%hhu)", &_key, &_value);
ActionAdd::ActionAdd(const Common::String &line) {
}

ResultAction *ActionAdd::clone() const {
	return new ActionAdd(*this);
}

bool ActionAdd::execute(ZVision *engine) {
	engine->getScriptManager()->addToStateValue(_key, _value);
	return true;
}


//////////////////////////////////////////////////////////////////////////////
// ActionAssign
//////////////////////////////////////////////////////////////////////////////

	sscanf(line->c_str(), ":assign(%u, %hhu)", &_key, &_value);
ActionAssign::ActionAssign(const Common::String &line) {
}

ResultAction *ActionAssign::clone() const {
	return new ActionAssign(*this);
}

bool ActionAssign::execute(ZVision *engine) {
	engine->getScriptManager()->setStateValue(_key, _value);
	return true;
}


//////////////////////////////////////////////////////////////////////////////
// ActionAttenuate
//////////////////////////////////////////////////////////////////////////////

	sscanf(line->c_str(), ":assign(%u, %hd)", &_key, &_attenuation);
ActionAttenuate::ActionAttenuate(const Common::String &line) {
}

ResultAction *ActionAttenuate::clone() const {
	return new ActionAttenuate(*this);
}

bool ActionAttenuate::execute(ZVision *engine) {
	// TODO: Implement
	return true;
}


//////////////////////////////////////////////////////////////////////////////
// ActionChangeLocation
//////////////////////////////////////////////////////////////////////////////

	sscanf(line->c_str(), ":change_location(%c,%c,%c%c,%hu)", &_world, &_room, &_node, &_view, &_x);
ActionChangeLocation::ActionChangeLocation(const Common::String &line) {
}

ResultAction *ActionChangeLocation::clone() const {
	return new ActionChangeLocation(*this);
}

bool ActionChangeLocation::execute(ZVision *engine) {
	// TODO: Implement
	return true;
}


//////////////////////////////////////////////////////////////////////////////
// ActionCrossfade
//////////////////////////////////////////////////////////////////////////////

	sscanf(line->c_str(), 
           ":crossfade(%u %u %hhu %hhu %hhu %hhu %hu)",
ActionCrossfade::ActionCrossfade(const Common::String &line) {
           &_keyOne, &_keyTwo, &_oneStartVolume, &_twoStartVolume, &_oneEndVolume, &_twoEndVolume, &_timeInMillis);
}

ResultAction *ActionCrossfade::clone() const {
	return new ActionCrossfade(*this);
}

bool ActionCrossfade::execute(ZVision *engine) {
	// TODO: Implement
	return true;
}


//////////////////////////////////////////////////////////////////////////////
// ActionPreloadAnimation
//////////////////////////////////////////////////////////////////////////////

	// The two %*hhu are always 0 and dont seem to have a use
	sscanf(line->c_str(), ":animpreload:%u(%s %*hhu %*hhu %u %hhu)", &_key, &_fileName, &_mask, &_framerate);
ActionPreloadAnimation::ActionPreloadAnimation(const Common::String &line) {
}

ResultAction *ActionPreloadAnimation::clone() const {
	return new ActionPreloadAnimation(*this);
}

bool ActionPreloadAnimation::execute(ZVision *engine) {
	// TODO: Implement
	return true;
}


//////////////////////////////////////////////////////////////////////////////
// ActionPlayAnimation
//////////////////////////////////////////////////////////////////////////////

	// The two %*hhu are always 0 and dont seem to have a use
	sscanf(line->c_str(), 
           ":animplay:%u(%s %u %u %u %u %u %u %hhu %*hhu %*hhu %u %hhu)",
ActionPlayAnimation::ActionPlayAnimation(const Common::String &line) {
           &_key, &_x, &_y, &_width, &_height, &_start, &_end, &_loop, &_mask, &_framerate);
}

ResultAction *ActionPlayAnimation::clone() const {
	return new ActionPlayAnimation(*this);
}

bool ActionPlayAnimation::execute(ZVision *engine) {
	// TODO: Implement
	return true;
}


//////////////////////////////////////////////////////////////////////////////
// ActionRandom
//////////////////////////////////////////////////////////////////////////////

	sscanf(line->c_str(), ":random:%u, %u)", &_key, &_max);
ActionRandom::ActionRandom(const Common::String &line) {
}

ResultAction *ActionRandom::clone() const {
	return new ActionRandom(*this);
}

bool ActionRandom::execute(ZVision *engine) {
	uint randNumber = engine->getRandomSource()->getRandomNumber(_max);
	engine->getScriptManager()->setStateValue(_key, randNumber);
	return true;
}


//////////////////////////////////////////////////////////////////////////////
// ActionTimer
//////////////////////////////////////////////////////////////////////////////

	sscanf(line->c_str(), ":timer:%u(%hu)", &_key, &_time);
ActionTimer::ActionTimer(const Common::String &line) {
}

ResultAction *ActionTimer::clone() const {
	return new ActionTimer(*this);
}

bool ActionTimer::execute(ZVision *engine) {
	engine->getScriptManager()->addActionNode(new NodeTimer(_key, _time));
	return true;
}

} // End of namespace ZVision
