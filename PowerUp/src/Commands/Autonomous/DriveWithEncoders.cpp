#include "DriveWithEncoders.h"
#include "../../Utilities/Log.h"
#include "../../RobotMap.h"

/**
 * distance in inches, speed from -1 to 1
 */
DriveWithEncoders::DriveWithEncoders(double distance, double speed)
{
	LOG("[DriveWithEncoders] Constructed");

	if (CommandBase::pDriveTrain != nullptr)
	{
		Requires(CommandBase::pDriveTrain);
		this->dDistance = distance;
		this->dSpeed = speed;
	}
	else
	{
		LOG("[DriveWithEncoders] driveTrain is null!");
	}

	this->pTimer = new Timer();

	return;
}

/**
 *
 */
DriveWithEncoders::~DriveWithEncoders()
{
	delete this->pTimer;
}

/**
 *
 */
void DriveWithEncoders::Initialize()
{
	LOG("[DriveWithEncoders] Initialized");

	this->pTimer->Reset();
	this->pTimer->Start();

	CommandBase::pDriveTrain->ResetEncoders();
	CommandBase::pDriveTrain->InitAutonomousMode(true); // invert right front motor
	CommandBase::pDriveTrain->Drive(dDistance, dSpeed);
	return;
}

/**
 *
 */
void DriveWithEncoders::Execute()
{
	if (iCounter++ == 10)
	{
		CommandBase::pDriveTrain->Trace();

		LOG("[DriveWithEncoders] Position Target: " << CommandBase::pDriveTrain->GetTargetPosition()
				<< " Current: " << CommandBase::pDriveTrain->GetLeftPosition()
				<< " Velocity: " << CommandBase::pDriveTrain->GetVelocity()
				<< " Time: "  << this->pTimer->Get());

		iCounter = 0;
	}

	return;
}

/**
 *
 */
bool DriveWithEncoders::IsFinished()
{
	if (this->pTimer->Get() > 5.0) // stop after 4 seconds no matter what
	{
		LOG("[DriveWithEncoder] Timed out");

		return true;
	}

	if (CommandBase::pDriveTrain->GetLeftPosition() >= (CommandBase::pDriveTrain->GetTargetPosition() - 500.0))
	{
		LOG("[DriveWithEncoder] Reached Target");

		return true;
	}

	return false;
}

/**
 *
 */
void DriveWithEncoders::End()
{
	LOG("[DriveWithEncoders] Ended" );

	CommandBase::pDriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void DriveWithEncoders::Interrupted()
{
	LOG("[DriveWithEncoders] Interrupted" );

	CommandBase::pDriveTrain->ResetDrive();

	return;
}
