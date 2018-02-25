#include "DriveWithJoystick.h"
#include "../Utilities/Log.h"
#include <math.h>
#include "../RobotMap.h"



DriveWithJoystick::DriveWithJoystick()
{
	LOG("[DriveWithJoystick] Constructed");

	if (CommandBase::pDriveTrain != nullptr)
	{
		Requires(CommandBase::pDriveTrain);
	}
	else
	{
		LOG("[DriveWithJoystick] driveTrain is null!");
	}

	return;
}


void DriveWithJoystick::Initialize()
{
	LOG("[DriveWithJoystick] Initialized");

	return;
}



void DriveWithJoystick::Execute()
{
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
