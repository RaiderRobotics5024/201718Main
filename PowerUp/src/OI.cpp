#include "OI.h"
#include "RobotMap.h"


OI::OI()
{
	std::cout << "[OI] Constructed" << std::endl;

	// NOTE: For some reason, Eclipse complains about not finding
	//	the XboxController class, even though it compiles 100% OK.
	this->pJoystickDrive = new XboxController(XBOX_CONTROLLER_DRIVE_PORT);
	this->pJoystickOperator = new XboxController(XBOX_CONTROLLER_OPERATOR_PORT);

	return;
}


OI::~OI()
{
	delete this->pJoystickDrive;
	delete this->pJoystickOperator;

	return;
}


frc::XboxController* OI::GetJoystickDrive()
{
	return this->pJoystickDrive;
}


frc::XboxController* OI::GetJoystickOperator()
{
	return this->pJoystickOperator;
}
