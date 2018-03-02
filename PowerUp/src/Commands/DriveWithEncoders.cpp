#include "DriveWithEncoders.h"
#include "../Utilities/Log.h"
#include "../RobotMap.h"

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

	return;
}

/**
 *
 */
void DriveWithEncoders::Initialize()
{
	LOG("[DriveWithEncoders] Initialized");

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
		iCounter = 0;
	}

	return;
}

/**
 *
 */
bool DriveWithEncoders::IsFinished()
{
//	return CommandBase::pDriveTrain->IsDriving();

	return CommandBase::pDriveTrain->GetLeftPosition() >= CommandBase::pDriveTrain->GetTargetPosition();
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
