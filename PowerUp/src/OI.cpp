#include "OI.h"

/**
 *
 */

OI::OI()
{
	std::cout << "[OI] Constructed" << std::endl;

	joystick = new XboxController(XBOX_CONTROLLER_DRIVE_PORT);
}

/**
 *
 */

frc::XboxController* OI::GetJoystick()
{
	return joystick;
}
