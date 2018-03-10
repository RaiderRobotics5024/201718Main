#include "ToggleIntake.h"
#include "../../Utilities/Log.h"
#include "../../RobotMap.h"

/**
 * speed from -1 to 1
 */
ToggleIntake::ToggleIntake(double speed)
{
	LOG("[EjectCube] Constructed");

	if (CommandBase::pIntake != nullptr)
	{
		Requires(CommandBase::pIntake);
		this->dSpeed = speed;
	}
	else
	{
		LOG("[EjectCube] inTake is null!");
	}

	this->pTimer = new Timer();

	return;
}

/**
 *
 */
void ToggleIntake::Initialize()
{
	LOG("[EjectCube] Initialized");

	this->pTimer->Reset();
	this->pTimer->Start();

	return;
}

/**
 *
 */
void ToggleIntake::Execute()
{
	CommandBase::pIntake->SetSpeed(dSpeed);

	return;
}

/**
 *
 */
bool ToggleIntake::IsFinished()
{
	if (this->pTimer->Get() > 0.5) // stop after 2 seconds no matter what
	{
		LOG("[EjectCube] Timed Out");

		return true;
	}

	return false;
}

/**
 *
 */
void ToggleIntake::End()
{
	LOG("[EjectCube] Ended");

	CommandBase::pIntake->Reset();

	return;
}

/**
 *
 */
void ToggleIntake::Interrupted()
{
	LOG("[EjectCube] Interrupted" );

	CommandBase::pIntake->Reset();

	return;
}
