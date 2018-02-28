/*
 * XBox_Trigger.h
 *
 *  Created on: Jun 24, 2014
 *      Author: Blar
 */

#ifndef XBoxPOV_H_
#define XBoxPOV_H_

#include "WPILib.h"

class XBoxPOV : public Trigger {
private:
	Joystick* joy;
	int target;

public:
	XBoxPOV(Joystick* joy, int target);
    bool Get();
};

#endif /* JoystickTriggers_H_ */
