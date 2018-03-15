#include "MoveElevator.h"
#include "../../Utilities/Log.h"
#include "../../RobotMap.h"

/**
 *
 */
MoveElevator::MoveElevator(Height::ElevatorHeight height)
{
	LOG("[MoveElevator] Constructed");

	if (CommandBase::pElevator != nullptr)
	{
		Requires(CommandBase::pElevator);
		this->ehHeight = height;
	}
	else
	{
		LOG("[MoveElevator] elevator is null!");
	}

	this->pTimer = new Timer();

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

	CommandBase::pElevator->Reset();
	CommandBase::pElevator->ResetCounters();

	return;
}

/**
 *
 */
void MoveElevator::Execute()
{
	switch (ehHeight)
	{
	case Height::BOTTOM : dMotorSpeed = -0.5; break; // go down until we hit bottom
	case Height::CUBEX2 : dMotorSpeed = -0.5; break; // go down until we hit cubex2 or bottom
	case Height::SWITCH : dMotorSpeed =  0.5; break; // go up until we hit switch
	}

	CommandBase::pElevator->SetMotorSpeed(dMotorSpeed);

	return;
}

/**
 *
 */
bool MoveElevator::IsFinished()
{
	switch (ehHeight)
	{
	case Height::BOTTOM :
		if (CommandBase::pElevator->IsBottomSwitchAligned()) return true;
		return this->pTimer->Get() > 2; // it should take a maximum of 2 seconds to reach the bottom from any position

	case Height::CUBEX2 :
		if (CommandBase::pElevator->IsMiddleSwitchAligned()) return true;
		if (CommandBase::pElevator->IsBottomSwitchAligned()) CommandBase::pElevator->SetMotorSpeed(0.5); //we are at the bottom so go up
		return false;

	case Height::SWITCH :
		return CommandBase::pElevator->IsTopSwitchAligned();

	default: return false;
	}
}

/**
 *
 */
void MoveElevator::End()
{
	LOG("[MoveElevator] Ended");

	CommandBase::pElevator->Reset();
	CommandBase::pElevator->ResetCounters();

	return;
}

/**
 *
 */
void MoveElevator::Interrupted()
{
	LOG("[MoveElevator] Interrupted" );

	CommandBase::pElevator->Reset();
	CommandBase::pElevator->ResetCounters();

	return;
}
