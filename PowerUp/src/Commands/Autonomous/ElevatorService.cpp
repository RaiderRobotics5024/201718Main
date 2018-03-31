#include "ElevatorService.h"
#include "../../Utilities/Log.h"

/**
 * We were having an issue with the elevator motor where once it got to it's desired height and the motor
 * was switched off, the elevator arms would drop due to gravity.  This service command runs
 * in parallel to other commands and will hold the elevator at requested height
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
	case Height::NONE   : break; // don't move the elevator

	case Height::BOTTOM :
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

	case Height::CUBEX2 :
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

	case Height::SWITCH :
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
