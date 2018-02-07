#include "OI.h"
#include "RobotMap.h"

/**
 *
 */

OI::OI()
{
	std::cout << "[OI] Constructed" << std::endl;

	this->pJoystick = new XboxController(XBOX_CONTROLLER_DRIVE_PORT);
}

/**
 *
 */

frc::XboxController* OI::GetJoystick()
{
	return this->pJoystick;
}
