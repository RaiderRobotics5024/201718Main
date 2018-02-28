/*
 * XBoxTrigger.cpp
 *
 *  Created on: Jun 24, 2014
 *      Author: Blar
 */

#include <Triggers/XBoxTrigger.h>

XBoxTrigger::XBoxTrigger(Joystick* joy, int port) {
	this->joy = joy;
	this->port = port;
}

bool XBoxTrigger::Get() {
    return joy->GetRawAxis(port);
}

