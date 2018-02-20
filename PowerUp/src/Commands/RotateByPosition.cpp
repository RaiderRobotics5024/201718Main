#include "RotateByPosition.h"
#include "../Utilities/Log.h"
#include "../RobotMap.h"

/**
 *
 */

RotateByPosition::RotateByPosition(double distance, double speed)
{
	LOG("[RotateByPosition] Constructed" );

	if (CommandBase::pDriveTrain != nullptr) {
		Requires(CommandBase::pDriveTrain);
		this->dDistance = distance;
		this->dSpeed = speed;
	} else {
		LOG("[RotateByPosition] driveTrain is null!");
	}

	return;
}

/**
 *
 */

void RotateByPosition::Initialize()
{
	LOG("[RotateByPosition] Initialized");

	CommandBase::pDriveTrain->ResetEncoders();
	CommandBase::pDriveTrain->InitAutonomous(false);
	CommandBase::pDriveTrain->Drive(dDistance, dSpeed);

	return;
}

/**
 *
 */

void RotateByPosition::Execute()
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

bool RotateByPosition::IsFinished()
{
	return CommandBase::pDriveTrain->IsTurning();
}

/**
 *
 */

void RotateByPosition::End()
{
	LOG("[RotateByPosition] Ended");

	CommandBase::pDriveTrain->ResetDrive();

	return;
}

/**
 *
 */

void RotateByPosition::Interrupted()
{
	LOG("[RotateByPosition] Interrupted");

	return;
}
