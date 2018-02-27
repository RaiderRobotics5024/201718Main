#include "ClimbScale.h"
#include "../Utilities/Log.h"

/**
 *
 */
ClimbScale::ClimbScale()
{
	LOG("[ClimbScale] Constructed");

	if (CommandBase::pClimbSystem != nullptr)
	{
		Requires( CommandBase::pClimbSystem );
	}
	else
	{
		LOG("[ClimbScale] climbSystem is NULL");
	}

	return;
}

/**
 *
 */
void ClimbScale::Initialize()
{
	LOG("[ClimbScale] Initialized");

	return;
}

/**
 *
 */
void ClimbScale::Execute()
{
	frc::XboxController* pJoyOperator = CommandBase::pOI->GetJoystickOperator();

	if (pJoyOperator->GetXButton())
	{
		CommandBase::pClimbSystem->ExtendArm(true);
	}

	if (pJoyOperator->GetYButton())
	{
		CommandBase::pClimbSystem->RetractArm(1.0);
	}
	else
	{
		CommandBase::pClimbSystem->RetractArm(0.0);
	}

	return;
}

/**
 *
 */
bool ClimbScale::IsFinished()
{
	return false;
}

/**
 *
 */
void ClimbScale::End()
{
	LOG("[ClimbScale] Ended");

	CommandBase::pClimbSystem->ExtendArm(false); // reset the solenoid

	return;
}

/**
 *
 */
void ClimbScale::Interrupted()
{
	LOG("[ClimbScale] Interrupted");

	return;
}
