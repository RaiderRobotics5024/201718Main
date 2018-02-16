#include <iostream>
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

	CommandBase::pDriveTrain->InitAutonomous(false);
	double targetPositionRotations = (dDistance / INCHES_PER_REVOLUTION) * TICKS_PER_REVOLUTION;
	CommandBase::pDriveTrain->Drive(dSpeed * targetPositionRotations);

	return;
}

/**
 *
 */

void RotateByPosition::Execute()
{
	if (iCounter++ == 10)
	{
		std::cout << "[DriveByPosition] Execute - " << CommandBase::pDriveTrain->GetPosition() << std::endl;
		iCounter = 0;
	}

	return;
}

/**
 *
 */

bool RotateByPosition::IsFinished()
{
	return CommandBase::pDriveTrain->IsDriving();
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
