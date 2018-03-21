#include "ToggleGripper.h"
#include "../../Utilities/Log.h"
#include "../../RobotMap.h"

/**
 * speed from -1 to 1
 */
ToggleGripper::ToggleGripper(Action::GripperAction state)
{
	LOG("[ToggleGripper] Constructed");

	if (CommandBase::pIntake != nullptr)
	{
		Requires(CommandBase::pIntake);
		this->gsState = state;
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
	if (gsState == Action::OPEN)
	{
		CommandBase::pIntake->OpenGripper();
	}
	else if (gsState == Action::CLOSE)
	{
		CommandBase::pIntake->CloseGripper();
	}
	else
	{
		LOG("[ToggleGripper] invalid input. use 1 for grip and -1 for release");
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
