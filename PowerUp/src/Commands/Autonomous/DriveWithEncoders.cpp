#include "DriveWithEncoders.h"
#include "../../Utilities/Log.h"

/**
 * distance in inches, speed from -1 to 1
 */
DriveWithEncoders::DriveWithEncoders(double distance, double speed, Height::Type height, double timeout)
{
	LOG("[DriveWithEncoders] Constructed");

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

	CommandBase::pDriveTrain->InitAutonomousMode();
	CommandBase::pDriveTrain->DriveSetup();
	CommandBase::pDriveTrain->Drive(dDistance, dSpeed);
	return;
}

/**
 *
 */
void DriveWithEncoders::Execute()
{
	// ask elevator service to move to our set height
	gElevatorHeight = this->htHeight;

	DriveWithEncoders::Trace();

	return;
}

/**
 *
 */
bool DriveWithEncoders::IsFinished()
{
	if (this->pTimer->Get() > dTimeout) // stop after dTimeout seconds no matter what
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
	if (iCounter++ == 2)
	{
		CommandBase::pDriveTrain->Trace();

		LOG("[DriveWithEncoders] TD: " << this->dDistance
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
