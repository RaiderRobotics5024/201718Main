#include "DriveWithJoystick.h"
#include <math.h>
#include "../RobotMap.h"

/**
 *
 */

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

/**
 *
 */

void DriveWithJoystick::Initialize()
{
	std::cout << "[DriveWithJoystick] Initialized" << std::endl;

	return;
}

/**
 *
 */

void DriveWithJoystick::Execute()
{
	//CommandBase::pDriveTrain->Drive(CommandBase::pOI->GetJoystick());

	double slowMode = 1.0;
	if(CommandBase::pOI->GetJoystickDrive()->GetAButton())
	{
		slowMode = 0.55;
	}

	double controlDirectionMode = 1.0;

	if(CommandBase::pOI->GetJoystickDrive()->GetBButton())
	{
		controlDirectionMode = -1.0;
	}

	double forwardSpeed = CommandBase::pOI->GetJoystickDrive()->GetY(XboxController::kLeftHand);
	double turnAngle = CommandBase::pOI->GetJoystickDrive()->GetX(XboxController::kLeftHand);

	if (fabs(forwardSpeed) <= XBOX_DEADZONE_LEFT_JOY)
	{
		forwardSpeed = 0.0;
	}

	if (fabs(turnAngle) <= XBOX_DEADZONE_LEFT_JOY)
	{
		turnAngle = 0.0;
	}

	forwardSpeed = forwardSpeed * controlDirectionMode * slowMode;
	turnAngle = turnAngle * slowMode;

	CommandBase::pDriveTrain->ArcadeDrive(forwardSpeed, turnAngle);

	return;
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
	return;
}

/**
 *
 */

void DriveWithJoystick::Interrupted()
{
	return;
}
