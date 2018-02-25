#include "ClimbScale.h"
#include "../Utilities/Log.h"

/**
 *
 */
ClimbScale::ClimbScale()
{
	LOG("[ClimbScale] Constructed");

	if ( CommandBase::pClimbSystem != nullptr )
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
	return;
}

/**
 *
 */
void ClimbScale::Execute()
{
	frc::XboxController* pJoyOperator = CommandBase::pOI->GetJoystickOperator();

	if ( pJoyOperator->GetAButton() )
	{
		CommandBase::pClimbSystem->ExtendArm();
	}
	else if ( pJoyOperator->GetYButton() )
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
