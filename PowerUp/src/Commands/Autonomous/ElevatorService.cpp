#include "ElevatorService.h"
#include "../../Utilities/Log.h"
#include "../../RobotMap.h"

/**
 *
 */
ElevatorService::ElevatorService()
{
	LOG("[ElevatorService] Constructed");

	if (CommandBase::pElevator != nullptr)
	{
		Requires(CommandBase::pElevator);
	}
	else
	{
		LOG("[ElevatorService] elevator is null!");
	}

	return;
}

/**
 *
 */
void ElevatorService::Initialize()
{
	LOG("[ElevatorService] Initialized");

	CommandBase::pElevator->Reset();

	return;
}

/**
 *
 */
void ElevatorService::Execute()
{
	if (ehCalledTo != gElevatorHeight)
	{
		ehCalledTo = gElevatorHeight;
		bArrived = false;
	}

	switch (ehCalledTo)
	{
	case BOTTOM :
		if (CommandBase::pElevator->IsBottomSwitchAligned())
		{
			dMotorSpeed = 0.0; // we arrived at the bottom so turn off the motor
			bArrived = true;
		}
		else
		{
			dMotorSpeed = 0.4; // set the motor to go down until we get to the bottom
		}
		break;

	case CUBEX2 :
		if (CommandBase::pElevator->IsMiddleSwitchAligned())
		{
			dMotorSpeed = 0.0;
			bArrived = true;
		}
		else if (CommandBase::pElevator->IsBottomSwitchAligned() || bArrived)
		{
			dMotorSpeed = -0.4; // we arrived at the bottom or we arrived but dropped down from gravity so go up
		}
		else
		{
			dMotorSpeed = 0.3; // go down until we hit the middle or bottom
		}
		break;

	case SWITCH :
		if (CommandBase::pElevator->IsTopSwitchAligned())
		{
			dMotorSpeed = 0.0; // we arrived at the switch so turn off the motor
			bArrived = true;
		}
		else
		{
			dMotorSpeed = -0.4; // go up because we haven't hit the top or we did and dropped from gravity
		}
		break;
	}

	CommandBase::pElevator->SetMotorSpeed(dMotorSpeed);

	return;
}

/**
 *
 */
bool ElevatorService::IsFinished()
{
	return false; // only stop if interrupted
}

/**
 *
 */
void ElevatorService::End()
{
	LOG("[ElevatorService] Ended");

	CommandBase::pElevator->Reset();

	return;
}

/**
 *
 */
void ElevatorService::Interrupted()
{
	LOG("[ElevatorService] Interrupted" );

	CommandBase::pElevator->Reset();

	return;
}
