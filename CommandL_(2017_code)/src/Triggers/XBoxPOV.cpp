/*
 * XBoxTrigger.cpp
 *
 *  Created on: Jun 24, 2014
 *      Author: Blar
 */

#include <Triggers/XBoxPOV.h>

XBoxPOV::XBoxPOV(Joystick* joy, int target) {
	this->joy = joy;
	this->target = target;
}

bool XBoxPOV::Get() {
    if(abs(joy->GetPOV() - target) == 0){ //tolarance
    	return true;
    }else{
    	return false;
    }
}

