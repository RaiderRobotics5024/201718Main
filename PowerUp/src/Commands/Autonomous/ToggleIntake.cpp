#include "ToggleIntake.h"
#include "../../Utilities/Log.h"
#include "../../RobotMap.h"

/**
 * speed from -1 to 1
 */
ToggleIntake::ToggleIntake(Cube::Type cube)
{
	LOG("[ToggleIntake] Constructed");

	if (CommandBase::pIntake != nullptr)
	{
		Requires(CommandBase::pIntake);
		this->ctCube = cube;
	}
	else
	{
		LOG("[ToggleIntake] inTake is null!");
	}

	this->pTimer = new Timer();

	return;
}

/**
 *
 */
void ToggleIntake::Initialize()
{
	LOG("[ToggleIntake] Initialized");

	this->pTimer->Reset();
	this->pTimer->Start();

	return;
}

/**
 *
 */
void ToggleIntake::Execute()
{
	if (ctCube == Cube::TAKEIN)
	{
		CommandBase::pIntake->OpenGripper();
	}
	else if (ctCube == Cube::EJECT)
	{
		CommandBase::pIntake->CloseGripper();
	}

	return;
}

/**
 *
 */
bool ToggleIntake::IsFinished()
{
	if (this->pTimer->Get() > 0.5) // stop after 2 seconds no matter what
	{
		LOG("[ToggleIntake] Timed Out");

		return true;
	}

	return false;
}

/**
 *
 */
void ToggleIntake::End()
{
	LOG("[ToggleIntake] Ended");

	CommandBase::pIntake->Reset();

	return;
}

/**
 *
 */
void ToggleIntake::Interrupted()
{
	LOG("[ToggleIntake] Interrupted" );

	CommandBase::pIntake->Reset();

	return;
}
