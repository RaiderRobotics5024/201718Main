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
	CommandBase::pClimbSystem->ExtendArm(CommandBase::pOI->GetJoystickOperator());
	CommandBase::pClimbSystem->RetractArm(CommandBase::pOI->GetJoystickOperator());

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
