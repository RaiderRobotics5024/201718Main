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
	CommandBase::pDriveTrain->InitAutonomousMode(true); // change this based on test or production (true) robot, (false) test robot
	CommandBase::pDriveTrain->Drive(dDistance, dSpeed);
	return;
}

/**
 *
 */
void DriveWithEncoders::Execute()
{
	if (iCounter++ == 5)
	{
		DriveWithEncoders::Trace();

		iCounter = 0;
	}

	return;
}

/**
 *
 */
bool DriveWithEncoders::IsFinished()
{
	if (this->pTimer->Get() > 5.0) // stop after 5 seconds no matter what
	{
		LOG("[DriveWithEncoder] Timed out");

		return true;
	}

	if (CommandBase::pDriveTrain->GetLeftPosition() >= (CommandBase::pDriveTrain->GetTargetPosition()))
	{
		LOG("[DriveWithEncoder] Reached Target by Left");

		return true;
	}

	if (CommandBase::pDriveTrain->GetRightPosition() >= (CommandBase::pDriveTrain->GetTargetPosition()))
	{
		LOG("[DriveWithEncoder] Reached Target by Right");

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

	DriveWithEncoders::Trace();

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

/**
 *
 */
void DriveWithEncoders::Trace()
{
	LOG("[DriveWithEncoders] TD: " << this->dDistance
			<< " CD: " << CommandBase::pDriveTrain->GetLeftDistance()
			<< " TP: " << CommandBase::pDriveTrain->GetTargetPosition()
			<< " LP: " << CommandBase::pDriveTrain->GetLeftPosition()
			<< " RP: " << CommandBase::pDriveTrain->GetRightPosition()
			<< " VL: " << CommandBase::pDriveTrain->GetVelocity()
			<< " Time: " << this->pTimer->Get());

	return;
}
