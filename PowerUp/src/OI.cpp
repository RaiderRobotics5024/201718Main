#include "OI.h"
#include "RobotMap.h"

/**
 *
 */

OI::OI()
{
	std::cout << "[OI] Constructed" << std::endl;

	// NOTE: For some reason, Eclipse complains about not finding
	//	the XboxController class, even though it compiles 100% OK.
	this->pJoystick = new XboxController(XBOX_CONTROLLER_DRIVE_PORT);

	return;
}

/**
 *
 */

frc::XboxController* OI::GetJoystick()
{
	return this->pJoystick;
}
