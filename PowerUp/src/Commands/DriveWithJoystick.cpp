#include "DriveWithJoystick.h"
#include "../Utilities/Log.h"

/**
 *
 */

DriveWithJoystick::DriveWithJoystick()
{
	LOG("[DriveWithJoystick] Constructed");

	if (CommandBase::pDriveTrain != nullptr)	{
		Requires(CommandBase::pDriveTrain);
	} else {
		LOG("[DriveWithJoystick] driveTrain is null!");
	}

	return;
}

/**
 *
 */

void DriveWithJoystick::Initialize()
{
	LOG("[DriveWithJoystick] Initialized");

	return;
}

/**
 *
 */

void DriveWithJoystick::Execute()
{
	CommandBase::pDriveTrain->Drive(CommandBase::pOI->GetJoystickDrive());
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
	LOG("[DriveWithJoystick] Ended");

	return;
}

/**
 *
 */

void DriveWithJoystick::Interrupted()
{
	LOG("[DriveWithJoystick] Interrupted");

	return;
}
