#include "RotateWithEncoders.h"
#include "../../Utilities/Log.h"
#include "../../RobotMap.h"

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

	this->pTimer = new Timer();

	return;
}

/**
 *
 */
RotateWithEncoders::~RotateWithEncoders()
{
	delete this->pTimer;
}

/**
 *
 */
void RotateWithEncoders::Initialize()
{
	LOG("[RotateWithEncoders] Initialized");

	this->pTimer->Reset();
	this->pTimer->Start();

	CommandBase::pDriveTrain->InitAutonomousMode(false); // don't invert right front motor
	CommandBase::pDriveTrain->ResetEncoders();
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
		LOG("[RotateWithEncoders] CP: " << CommandBase::pDriveTrain->GetLeftPosition() << " TP: " << CommandBase::pDriveTrain->GetTargetPosition());

		iCounter = 0;
	}

	return;
}

/**
 *
 */
bool RotateWithEncoders::IsFinished()
{
	if (this->pTimer->Get() > 3.0) // stop after 2 seconds no matter what
	{
		LOG("[RotateWithEncoders] Timed out");

		return true;
	}

	if (CommandBase::pDriveTrain->IsTurning())
	{
		LOG("[RotateWithEncoders] Angle Reached");

		return true;
	}

	return false;
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
