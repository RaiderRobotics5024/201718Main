#include "ToggleGripper.h"
#include "../../Utilities/Log.h"
#include "../../RobotMap.h"

/**
 * speed from -1 to 1
 */
ToggleGripper::ToggleGripper(double type)
{
	LOG("[ToggleGripper] Constructed");

	if (CommandBase::pIntake != nullptr)
	{
		Requires(CommandBase::pIntake);
		this->dType = type;
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
	if (dType == -1)
	{
		CommandBase::pIntake->OpenGripper();
	}
	else if (dType == 1)
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
