#include "KeepElevatorAtTop.h"
#include "../../Utilities/Log.h"
#include "../../RobotMap.h"

/**
 *
 */
KeepElevatorAtTop::KeepElevatorAtTop()
{
	LOG("[KeepElevatorAtTop] Constructed");

	if (CommandBase::pElevator != nullptr)
	{
		Requires(CommandBase::pElevator);
	}
	else
	{
		LOG("[KeepElevatorAtTop] elevator is null!");
	}

	return;
}

/**
 *
 */
void KeepElevatorAtTop::Initialize()
{
	LOG("[KeepElevatorAtTop] Initialized");

	CommandBase::pElevator->Reset();

	return;
}

/**
 *
 */
void KeepElevatorAtTop::Execute()
{
	if (CommandBase::pElevator->IsTopSwitchAligned())
	{
		dMotorSpeed = 0.0;
	}
	else
	{
		dMotorSpeed = -0.1;
	}

	CommandBase::pElevator->SetMotorSpeed(dMotorSpeed);

	return;
}

/**
 *
 */
bool KeepElevatorAtTop::IsFinished()
{
	return false;
}

/**
 *
 */
void KeepElevatorAtTop::End()
{
	LOG("[KeepElevatorAtTop] Ended");

	CommandBase::pElevator->Reset();

	return;
}

/**
 *
 */
void KeepElevatorAtTop::Interrupted()
{
	LOG("[KeepElevatorAtTop] Interrupted" );

	CommandBase::pElevator->Reset();

	return;
}
