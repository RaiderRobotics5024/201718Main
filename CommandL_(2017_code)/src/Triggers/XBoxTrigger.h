/*
 * XBox_Trigger.h
 *
 *  Created on: Jun 24, 2014
 *      Author: Blar
 */

#ifndef XBoxTrigger_H_
#define XBoxTrigger_H_

#include "WPILib.h"

class XBoxTrigger : public Trigger {
private:
	Joystick* joy;
	int port;

public:
	XBoxTrigger(Joystick* joy, int port);
    bool Get();
};

#endif /* JoystickTriggers_H_ */
