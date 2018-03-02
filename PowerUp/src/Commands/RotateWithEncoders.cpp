#include "RotateWithEncoders.h"
#include "../Utilities/Log.h"
#include "../RobotMap.h"

/**
 *
 */
RotateWithEncoders::RotateWithEncoders(double distance, double speed)
{
	LOG("[RotateWithEncoders] Constructed" );

	if (CommandBase::pDriveTrain != nullptr)
	{
		Requires(CommandBase::pDriveTrain);
		this->dDistance = distance;
		this->dSpeed = speed;
	}
	else
	{
		LOG("[RotateWithEncoders] driveTrain is null!");
	}

	return;
}

/**
 *
 */
void RotateWithEncoders::Initialize()
{
	LOG("[RotateByPosition] Initialized");

	CommandBase::pDriveTrain->ResetEncoders();
	CommandBase::pDriveTrain->InitAutonomousMode(false); // don't invert right front motor
	CommandBase::pDriveTrain->Drive(dDistance, dSpeed);

	return;
}

/**
 *
 */
void RotateWithEncoders::Execute()
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
bool RotateWithEncoders::IsFinished()
{
	return CommandBase::pDriveTrain->IsTurning();
}

/**
 *
 */
void RotateWithEncoders::End()
{
	LOG("[RotateWithEncoders] Ended");

	CommandBase::pDriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void RotateWithEncoders::Interrupted()
{
	LOG("[RotateWithEncoders] Interrupted");

	return;
}
