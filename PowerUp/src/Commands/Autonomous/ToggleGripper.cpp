#include "ToggleGripper.h"
#include "../../Utilities/Log.h"
#include "../../RobotMap.h"

/**
 * speed from -1 to 1
 */
ToggleGripper::ToggleGripper(Action::Type action)
{
	LOG("[ToggleGripper] Constructed");

	if (CommandBase::pIntake != nullptr)
	{
		Requires(CommandBase::pIntake);
		this->atAction = action;
	}
	else
	{
		LOG("[ToggleGripper] inTake is null!");
	}

	this->pTimer = new Timer();

	return;
}

/**
 *
 */
void ToggleGripper::Initialize()
{
	LOG("[ToggleGripper] Initialized");

	this->pTimer->Reset();
	this->pTimer->Start();

	return;
}

/**
 *
 */
void ToggleGripper::Execute()
{
	if (atAction == Action::OPEN)
	{
		CommandBase::pIntake->OpenGripper();
	}
	else if (atAction == Action::CLOSE)
	{
		CommandBase::pIntake->CloseGripper();
	}

	return;
}

/**
 *
 */
bool ToggleGripper::IsFinished()
{
	if (this->pTimer->Get() > 0.5) // stop after 2 seconds no matter what
	{
		LOG("[ToggleGripper] Timed Out");

		return true;
	}

	return false;
}

/**
 *
 */
void ToggleGripper::End()
{
	LOG("[ToggleGripper] Ended");

	CommandBase::pIntake->Reset();

	return;
}

/**
 *
 */
void ToggleGripper::Interrupted()
{
	LOG("[ToggleGripper] Interrupted" );

	CommandBase::pIntake->Reset();

	return;
}
