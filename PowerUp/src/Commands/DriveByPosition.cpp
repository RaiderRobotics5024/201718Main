#include "DriveByPosition.h"
#include "../Utilities/Log.h"
#include "../RobotMap.h"

/**
 * distance in inches, speed from -1 to 1
 */

DriveByPosition::DriveByPosition(double distance, double speed)
{
	LOG("[DriveByPosition] Constructed");

	if (CommandBase::pDriveTrain != nullptr) {
		Requires(CommandBase::pDriveTrain);
		this->dDistance = distance;
		this->dSpeed = speed;
	} else {
		LOG("[DriveByPosition] driveTrain is null!");
	}

	return;
}

/**
 *
 */

void DriveByPosition::Initialize()
{
	LOG("[DriveByPosition] Initialized");

	CommandBase::pDriveTrain->ResetEncoders();
	CommandBase::pDriveTrain->InitAutonomous(true);
	CommandBase::pDriveTrain->Drive(dDistance, dSpeed);

	return;
}

/**
 *
 */

void DriveByPosition::Execute()
{
	if (iCounter++ == 10)
	{
		CommandBase::pDriveTrain->Trace();
		iCounter = 0;
	}

	return;
}

/**
 *
 */

bool DriveByPosition::IsFinished()
{
	return CommandBase::pDriveTrain->IsDriving();
}

/**
 *
 */

void DriveByPosition::End()
{
	LOG("[DriveByPosition] Ended" );

	CommandBase::pDriveTrain->ResetDrive();

	return;
}

/**
 *
 */

void DriveByPosition::Interrupted()
{

	return;
}
