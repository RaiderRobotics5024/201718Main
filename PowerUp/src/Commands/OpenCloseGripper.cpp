#include "OpenCloseGripper.h"
#include "../Utilities/Log.h"
#include "../RobotMap.h"

/**
 * speed from -1 to 1
 */
OpenCloseGripper::OpenCloseGripper(double type)
{
	LOG("[OpenCloseGripper] Constructed");

	if (CommandBase::pIntake != nullptr)
	{
		Requires(CommandBase::pIntake);
		this->dType = type;
	}
	else
	{
		LOG("[OpenCloseGripper] inTake is null!");
	}

	this->pTimer = new Timer();

	return;
}

/**
 *
 */
void OpenCloseGripper::Initialize()
{
	LOG("[OpenCloseGripper] Initialized");

	this->pTimer->Reset();
	this->pTimer->Start();

	return;
}

/**
 *
 */
void OpenCloseGripper::Execute()
{
	if (dType = -1){
		CommandBase::pIntake->OpenGripper();
	} else if (dType = 1) {
		CommandBase::pIntake->CloseGripper();
	} else {
		LOG("[OpenCloseGripper] invalid input. use 1 for grip and -1 for release");
	}

	return;
}

/**
 *
 */
bool OpenCloseGripper::IsFinished()
{
	if (this->pTimer->Get() > 0.5) // stop after 2 seconds no matter what
	{
		LOG("[OpenCloseGripper] Timed Out");

		return true;
	}

	return false;
}

/**
 *
 */
void OpenCloseGripper::End()
{
	LOG("[OpenCloseGripper] Ended");

	CommandBase::pIntake->Reset();

	return;
}

/**
 *
 */
void OpenCloseGripper::Interrupted()
{
	LOG("[OpenCloseGripper] Interrupted" );

	CommandBase::pIntake->Reset();

	return;
}
