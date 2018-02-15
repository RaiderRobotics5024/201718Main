#include <iostream>
#include "RotateToAngle.h"
#include "../Utilities/Log.h"

/**
 *
 */

RotateToAngle::RotateToAngle(double setpoint)
{
	LOG("[RotateToAngle] Constructed");

	if (CommandBase::pDriveTrain != nullptr) {
		Requires(CommandBase::pDriveTrain);
		this->dSetPoint = setpoint;
	} else {
		LOG("[RotateToAngle] driveTrain is null!");
	}

	return;
}

/**
 *
 */

void RotateToAngle::Initialize()
{
	LOG("[RotateToAngle] Initalized");

	CommandBase::pDriveTrain->ResetGyro();
	CommandBase::pDriveTrain->Turn(dSetPoint);

	return;
}

/**
 *
 */

void RotateToAngle::Execute()
{

	if (iCounter++ == 10)
	{
		std::cout << "[RotateToAngle] Execute - Gyro Angle: " << CommandBase::pDriveTrain->GetAngle() << std::endl;
		iCounter = 0;
	}

	return;
}

/**
 *
 */

bool RotateToAngle::IsFinished()
{
	return CommandBase::pDriveTrain->GetAngle() == dSetPoint;
}

/**
 *
 */

void RotateToAngle::End()
{

	return;
}

/**
 *
 */

void RotateToAngle::Interrupted()
{

	return;
}
