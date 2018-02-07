#ifndef _OI_HG_
#define _OI_HG_

#include <iostream>
#include <WPILib.h>
#include <XboxController.h>

/**
 *
 */

class OI
{
public:
	OI();
	frc::XboxController* GetJoystick();

private:
	frc::XboxController* pJoystick;
};

#endif
