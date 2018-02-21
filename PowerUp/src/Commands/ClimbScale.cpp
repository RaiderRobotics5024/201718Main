#include "ClimbScale.h"
#include <iostream>

ClimbScale::ClimbScale()
{
	std::cout << "[ClimbScale] Constructed" << std::endl;

	if ( CommandBase::pClimbSystem != nullptr )
	{
		Requires( CommandBase::pClimbSystem );
	}
	else
	{
		std::cout << "[ClimbScale] ClimbSystem is NULL" << std::endl;
	}

	return;
}
void ClimbScale::Initialize()
{

	return;
}

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

bool ClimbScale::IsFinished()
{
	return false;
}

void ClimbScale::End()
{
	return;
}

void ClimbScale::Interrupted()
{
	return;
}



