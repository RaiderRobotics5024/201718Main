#include "Gripper.h"
#include <math.h>
#include "../RobotMap.h"


Gripper::Gripper()
{
	std::cout << "[Gripper] Constructed" << std::endl;

	if ( CommandBase::pIntake != nullptr )
	{
		Requires(CommandBase::pIntake);
	}
	else
	{
		std::cout << "[Gripper] driveTrain is NULL!" << std::endl;
	}

	return;
}

void Gripper::Initialize()
{
	std::cout << "[Gripper] Initialize" << std::endl;

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










