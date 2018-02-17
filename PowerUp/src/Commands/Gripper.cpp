#include "Gripper.h"
#include <math.h>
#include "../RobotMap.h"



Gripper::Gripper()
{
	std::cout << "[Gripper] Constructed" << std::endl;

	if (CommandBase::pIntake != nullptr)
	{
		Requires(CommandBase::pIntake);
	}
	else
	{
		std::cout << "[Gripper] driveTrain is null!" << std::endl;
	}

	return;
}


void Gripper::Initialize()
{
	std::cout << "[Gripper] Initialized" << std::endl;

	return;
}



void Gripper::Execute()
{
	//CommandBase::pDriveTrain->Drive(CommandBase::pOI->GetJoystick());

//	if (CommandBase::pOI->GetJoystickDrive()->GetAButton())
//	{
//	       //close grippers
//	       CommandBase::pIntake->OpenCloseIntake(frc::DoubleSolenoid::Value::kForward);
//
//	} else if(CommandBase::pOI->GetJoystickDrive()->GetBButton())
//	{
//	       //open gripper
//	       CommandBase::pIntake->OpenCloseIntake(frc::DoubleSolenoid::Value::kReverse);
//			//this->pGripperSolenoid->Set(kdirection);
//	 };
	CommandBase::pIntake->OpenCloseIntake();
	CommandBase::pIntake->BeltIntake();

	//double inSpeed = CommandBase::pOI->GetJoystickDrive()->GetTriggerAxis(XboxController::kLeftHand);
	//double outSpeed = CommandBase::pOI->GetJoystickDrive()->GetTriggerAxis(XboxController::kRightHand);

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


