#include "MoveElevator.h"
#include "../../Utilities/Log.h"
#include "../../RobotMap.h"

/**
 *
 */
MoveElevator::MoveElevator(double pos)
{
	LOG("[MoveElevator] Constructed");

	if (CommandBase::pElevator != nullptr)
	{
		Requires(CommandBase::pElevator);
		this->dPos = pos;
	}
	else
	{
		LOG("[MoveElevator] inTake is null!");
	}

	this->pTimer = new Timer();
	CommandBase::pElevator->ResetCounters();

	return;
}

/**
 *
 */
void MoveElevator::Initialize()
{
	LOG("[MoveElevator] Initialized");

	this->pTimer->Reset();
	this->pTimer->Start();

	return;
}

/**
 *
 */
void MoveElevator::Execute()
{
	if (dPos == 1)
	{
		dMotorSpeed = 0.5;
	}
	else if (dPos == 0)
	{
		dMotorSpeed = -0.5;
	}
	else
	{
		dMotorSpeed = 0;
	}

	CommandBase::pElevator->SetMotorSpeed(dMotorSpeed);

	if (CommandBase::pElevator->IsTopSwitchAligned() && dMotorSpeed > 0.0)
	{
		LOG("[ControlElevator] At the top" );

		dMotorSpeed = 0; // don't let the motor go passed the top switch
		CommandBase::pElevator->ResetCounters();
	}
	if (CommandBase::pElevator->IsBottomSwitchAligned() && dMotorSpeed > 0.0)
	{
		LOG("[ControlElevator] At the bottom" );

		dMotorSpeed = 0; // don't let the motor go passed the top switch
		CommandBase::pElevator->ResetCounters();
	}

	return;
}

/**
 *
 */
bool MoveElevator::IsFinished()
{
	if (this->pTimer->Get() > 0.5) // stop after 2 seconds no matter what
	{
		LOG("[MoveElevator] Timed Out");

		return true;
	}

	return false;
}

/**
 *
 */
void MoveElevator::End()
{
	LOG("[MoveElevator] Ended");

	CommandBase::pElevator->Reset();

	return;
}

/**
 *
 */
void MoveElevator::Interrupted()
{
	LOG("[MoveElevator] Interrupted" );

	CommandBase::pElevator->Reset();

	return;
}
