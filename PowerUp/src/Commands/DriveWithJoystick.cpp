#include "DriveWithJoystick.h"

/**
 *
 */

DriveWithJoystick::DriveWithJoystick()
{
	std::cout << "[DriveWithJoystick] Constructed" << std::endl;

	if (CommandBase::pDriveTrain != nullptr)	{
		Requires(CommandBase::pDriveTrain);
	} else {
		std::cout << "[DriveWithJoystick] driveTrain is null!" << std::endl;
	}
}

/**
 *
 */

void DriveWithJoystick::Initialize()
{
	std::cout << "[DriveWithJoystick] Initialized" << std::endl;
}

/**
 *
 */

void DriveWithJoystick::Execute()
{
	std::cout << "[DriveWithJoystick] Executing" << std::endl;

	CommandBase::pDriveTrain->Drive(CommandBase::pOI->GetJoystick());
}

/**
 *
 */

bool DriveWithJoystick::IsFinished()
{
	return false;
}

/**
 *
 */

void DriveWithJoystick::End()
{

}

/**
 *
 */

void DriveWithJoystick::Interrupted()
{

}
