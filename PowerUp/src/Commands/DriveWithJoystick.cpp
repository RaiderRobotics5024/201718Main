#include "DriveWithJoystick.h"
#include <math.h>
#include "../RobotMap.h"



DriveWithJoystick::DriveWithJoystick()
{
	std::cout << "[DriveWithJoystick] Constructed" << std::endl;

	if (CommandBase::pDriveTrain != nullptr)
	{
		Requires(CommandBase::pDriveTrain);
	}
	else
	{
		std::cout << "[DriveWithJoystick] driveTrain is null!" << std::endl;
	}

	return;
}


void DriveWithJoystick::Initialize()
{
	std::cout << "[DriveWithJoystick] Initialized" << std::endl;

	return;
}



void DriveWithJoystick::Execute()
{
	//CommandBase::pDriveTrain->Drive(CommandBase::pOI->GetJoystick());

	frc::XboxController* pJoyDrive = CommandBase::pOI->GetJoystickDrive();

	double forwardSpeed = pJoyDrive->GetY(XboxController::kLeftHand);
	double turnAngle = pJoyDrive->GetX(XboxController::kLeftHand);

	if (fabs(forwardSpeed) <= XBOX_DEADZONE_LEFT_JOY)
	{
		forwardSpeed = 0.0;
	}

	if (fabs(turnAngle) <= XBOX_DEADZONE_LEFT_JOY)
	{
		turnAngle = 0.0;
	}

	CommandBase::pDriveTrain->ArcadeDrive( forwardSpeed, turnAngle );

	return;
}



bool DriveWithJoystick::IsFinished()
{
	return false;
}



void DriveWithJoystick::End()
{
	return;
}



void DriveWithJoystick::Interrupted()
{
	return;
}

