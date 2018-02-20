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
		Requires(CommandBase::pClimbSystem);
	}
	else
	{
		LOG("[ClimbScale] climbSystem is null!");
	}

	return;
}

/**
 *
 */

void ClimbScale::Initialize()
{
	LOG("[ClimbScale] has been Initalized");

	return;
}

/**
 *
 */

void ClimbScale::Execute()
{
	if (CommandBase::pOI->GetJoystickOperator()->GetAButtonPressed())
	{
	   	CommandBase::pClimbSystem->ExtendArm();
	}

	else if (CommandBase::pOI->GetJoystickOperator()->GetYButtonPressed())
	{
		CommandBase::pClimbSystem->RetractArm();
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
	return;
}

/**
 *
 */

void ClimbScale::Interrupted()
{
	return;
}
