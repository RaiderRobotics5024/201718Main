#include "RotateWithEncoders.h"
#include "../../Utilities/Log.h"
#include "../../RobotMap.h"

/**
 *
 */
RotateWithEncoders::RotateWithEncoders(double distance, double speed, Height::Type height, double timeout)
{
	LOG("[RotateWithEncoders] Constructed" );

	if (CommandBase::pDriveTrain != nullptr)
	{
		Requires(CommandBase::pDriveTrain);
		this->dDistance = distance;
		this->dSpeed = speed;
		this->htHeight = height;
		this->dTimeout = timeout;
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

	CommandBase::pDriveTrain->InitAutonomousMode();
	CommandBase::pDriveTrain->DriveSetup();
	CommandBase::pDriveTrain->Drive(dDistance, dSpeed);

	return;
}

/**
 *
 */
void RotateWithEncoders::Execute()
{
	// ask elevator service to move to our set height
	gElevatorHeight = this->htHeight;

	RotateWithEncoders::Trace();

	return;
}

/**
 *
 */
bool RotateWithEncoders::IsFinished()
{
	if (this->pTimer->Get() > dTimeout) // stop after dTimeout seconds no matter what
	{
		LOG("[RotateWithEncoders] Timed out");

		return true;
	}

	if (CommandBase::pDriveTrain->GetLeftPosition() >= (CommandBase::pDriveTrain->GetTargetPosition()))
	{
		LOG("[RotateWithEncoders] Reached Target by Left");

		return true;
	}

	if (CommandBase::pDriveTrain->GetRightPosition() >= (CommandBase::pDriveTrain->GetTargetPosition()))
	{
		LOG("[RotateWithEncoders] Reached Target by Right");

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

/**
 *
 */
void RotateWithEncoders::Trace()
{
	if (iCounter++ == 10)
	{
		CommandBase::pDriveTrain->Trace();

		LOG("[RotateWithEncoders]"
			<< " TD: " << this->dDistance
			<< " TP: " << CommandBase::pDriveTrain->GetTargetPosition()
			<< " LD: " << CommandBase::pDriveTrain->GetLeftDistance()
			<< " LP: " << CommandBase::pDriveTrain->GetLeftPosition()
			<< " LV: " << CommandBase::pDriveTrain->GetLeftVelocity()
			<< " LE: " << CommandBase::pDriveTrain->GetLeftClosedLoopError()
			<< " RD: " << CommandBase::pDriveTrain->GetRightDistance()
			<< " RP: " << CommandBase::pDriveTrain->GetRightPosition()
			<< " RV: " << CommandBase::pDriveTrain->GetRightVelocity()
			<< " RE: " << CommandBase::pDriveTrain->GetRightClosedLoopError()
			<< " Time: " << this->pTimer->Get());

		iCounter = 0;
	}

	return;
}
