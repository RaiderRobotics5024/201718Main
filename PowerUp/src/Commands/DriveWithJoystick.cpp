#include "DriveWithJoystick.h"
#include "../Utilities/Log.h"
#include <math.h>
#include "../RobotMap.h"

/**
 *
 */
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

/**
 *
 */
DriveWithJoystick::~DriveWithJoystick()
{
	LOG("[DriveWithJoystick] Destroyed");

	return;
}

/**
 *
 */
void DriveWithJoystick::Initialize()
{
	LOG("[DriveWithJoystick] Initialized");

	this->isReverse = false;

	return;
}

/**
 *
 */
void DriveWithJoystick::Execute()
{
	frc::XboxController* pJoyDrive = CommandBase::pOI->GetJoystickDrive();

	if (pJoyDrive->GetXButtonReleased())
	{
		this->isReverse = !this->isReverse;
	}

	double xSpeed    = pJoyDrive->GetY(XboxController::kLeftHand);
	double zRotation = pJoyDrive->GetX(XboxController::kLeftHand);

	double dSlow = (pJoyDrive->GetBumper(XboxController::kRightHand)) ? 0.5 : 1;
	double dReverse = (this->isReverse) ? -1 : 1;

	if (fabs(xSpeed) <= XBOX_DEADZONE_LEFT_JOY)
	{
		xSpeed = 0.0;
	}

	if (fabs(zRotation) <= XBOX_DEADZONE_LEFT_JOY)
	{
		zRotation = 0.0;
	}

//	CommandBase::pDriveTrain->ArcadeDrive(xSpeed, zRotation);
	CommandBase::pDriveTrain->ArcadeDrive((xSpeed * dSlow * dReverse), (zRotation * dSlow));

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
