#include "Gripper.h"
#include "../Utilities/Log.h"
#include <math.h>
#include "../RobotMap.h"


Gripper::Gripper()
{
	LOG("[Gripper] Constructed");

	if ( CommandBase::pIntake != nullptr )
	{
		Requires(CommandBase::pIntake);
	}
	else
	{
		LOG("[Gripper] intake is NULL!");
	}

	return;
}

void Gripper::Initialize()
{
	LOG("[Gripper] Initialize");

	return;
}

void Gripper::Execute()
{
	CommandBase::pIntake->OpenCloseIntake();
	CommandBase::pIntake->BeltIntake();

	return;
}

bool Gripper::IsFinished()
{
	return false;
}


void Gripper::End()
{
	return;
}


void Gripper::Interrupted()
{
	return;
}
