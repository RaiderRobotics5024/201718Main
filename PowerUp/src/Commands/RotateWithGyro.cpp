#include "RotateWithGyro.h"
#include "../Utilities/Log.h"

/**
 *
 */
RotateWithGyro::RotateWithGyro(double setpoint)
{
	LOG("[RotateWithGyro] Constructed");

	if (CommandBase::pDriveTrain != nullptr)
	{
		Requires(CommandBase::pDriveTrain);
		this->dSetPoint = setpoint;
	}
	else
	{
		LOG("[RotateWithGyro] driveTrain is null!");
	}

	return;
}

/**
 *
 */
void RotateWithGyro::Initialize()
{
	LOG("[RotateWithGyro] Initalized");

	CommandBase::pDriveTrain->ResetGyro();
	CommandBase::pDriveTrain->Turn(dSetPoint);

	return;
}

/**
 *
 */
void RotateWithGyro::Execute()
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
bool RotateWithGyro::IsFinished()
{
	return CommandBase::pDriveTrain->GetAngle() == dSetPoint;
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
