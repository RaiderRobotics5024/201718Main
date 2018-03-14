#include "IntakeDriveWithEncoders.h"
#include "../Utilities/Log.h"
#include "../RobotMap.h"

/**
 * distance in inches, speed from -1 to 1
 */
 
 // IntakeDriveWithEncoders(distance, speed, intake);
IntakeDriveWithEncoders::IntakeDriveWithEncoders(double distance, double speed, double intakespeed)
{
	LOG("[IntakeDriveWithEncoders] Constructed");

	if (CommandBase::pDriveTrain != nullptr)
	{
		Requires(CommandBase::pDriveTrain);
		this->dDistance = distance;
		this->dSpeed = speed;
		this->dIntakeSpeed = intakespeed;
	}
	else
	{
		LOG("[IntakeDriveWithEncoders] driveTrain or Intake is null!");
	}

	this->pTimer = new Timer();

	return;
}

/**
 *
 */
IntakeDriveWithEncoders::~IntakeDriveWithEncoders()
{
	delete this->pTimer;
}

/**
 *
 */
void IntakeDriveWithEncoders::Initialize()
{
	LOG("[IntakeDriveWithEncoders] Initialized");

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
void IntakeDriveWithEncoders::Execute()
{
	if (iCounter++ == 10)
	{
		CommandBase::pDriveTrain->Trace();

		LOG("[IntakeDriveWithEncoders] Current Position: " << CommandBase::pDriveTrain->GetLeftPosition() << " Target Position: " << CommandBase::pDriveTrain->GetTargetPosition());

		LOG("[IntakeDriveWithEncoders] Time: "  << this->pTimer->Get());

		iCounter = 0;
	}
	
	//Intake
	CommandBase::pIntake->SetSpeed(dIntakeSpeed);

	return;
}

/**
 *
 */
bool IntakeDriveWithEncoders::IsFinished()
{
//	return CommandBase::pDriveTrain->IsDriving();

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
void IntakeDriveWithEncoders::End()
{
	LOG("[IntakeDriveWithEncoders] Ended" );

	CommandBase::pDriveTrain->ResetDrive();
	CommandBase::pIntake->Reset();

	return;
}

/**
 *
 */
void IntakeDriveWithEncoders::Interrupted()
{
	LOG("[IntakeDriveWithEncoders] Interrupted" );

	CommandBase::pDriveTrain->ResetDrive();
	CommandBase::pIntake->Reset();

	return;
}
