#include "RotateWithGyro.h"
#include "../../Utilities/Log.h"
#include "../../Subsystems/DriveTrainMap.h"
#include <math.h>

/**
 *
 */
RotateWithGyro::RotateWithGyro(double setpoint)
{
	LOG("[RotateWithGyro] Constructed");

	if (CommandBase::pDriveTrain != nullptr)
	{
		Requires(CommandBase::pDriveTrain);
		this->dSetpoint = setpoint;
	}
	else
	{
		LOG("[RotateWithGyro] driveTrain is null!");
	}

	this->pTimer = new Timer();

	return;
}

/**
 *
 */
void RotateWithGyro::Initialize()
{
	LOG("[RotateWithGyro] Initalized");

	this->pTimer->Reset();
	this->pTimer->Start();

	CommandBase::pDriveTrain->ResetGyro();
	CommandBase::pDriveTrain->TurnSetup();
	CommandBase::pDriveTrain->SetSetpoint(dSetpoint);
	CommandBase::pDriveTrain->Turn();

	return;
}

/**
 *
 */
void RotateWithGyro::Execute()
{
	RotateWithGyro::Trace();

	return;
}

/**
 *
 */
bool RotateWithGyro::IsFinished()
{
	if (this->pTimer->Get() > 2) // stop after 2 seconds no matter what
	{
		LOG("[RotateWithEncoders] Timed out");

		return true;
	}

	if (CommandBase::pDriveTrain->GetAngle() >= (this->dSetpoint - GYRO_TOLERANCE_DEGREES) &&
	    CommandBase::pDriveTrain->GetAngle() <= (this->dSetpoint + GYRO_TOLERANCE_DEGREES) && pTimer->Get() > 0)
	{
		LOG("[RotateWithEncoders] Reached Turn Angle");

		return true;
	}

	return false;
}

/**
 *
 */
void RotateWithGyro::End()
{
	LOG("[RotateWithGyro] Ended");

	return;
}

/**
 *
 */
void RotateWithGyro::Interrupted()
{
	LOG("[RotateWithGyro] Interrupted");

	return;
}

/**
 *
 */
void RotateWithGyro::Trace()
{
	if (iCounter++ == 10)
	{
		CommandBase::pDriveTrain->Trace();

		LOG("[RotateWithGyro] TA: " << dSetpoint
				<< " CA: "   << CommandBase::pDriveTrain->GetAngle()
				<< " Rate: " << CommandBase::pDriveTrain->GetRotateToAngleRate()
				<< " Time: " << this->pTimer->Get());


		iCounter = 0;
	}

	return;
}
