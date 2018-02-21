#include "ControlElevator.h"
#include <iostream>


ControlElevator::ControlElevator()
{
	std::cout << "[ControlElevator] Constructed" << std::endl;

	if ( CommandBase::pElevator != nullptr )
	{
		Requires(CommandBase::pElevator);
	}
	else
	{
		std::cout << "[ControlElevator] elevator is NULL!" << std::endl;
	}

	return;
}


void ControlElevator::Initialize()
{
	std::cout << "[ControlElevator] Constructed" << std::endl;

	return;
}


void ControlElevator::Execute()
{
	frc::XboxController* pJoyOperator = CommandBase::pOI->GetJoystickOperator();

	double rightOpTriggerAxis = pJoyOperator->GetTriggerAxis(frc::XboxController::kRightHand);
	double leftOpTriggerAxis = pJoyOperator->GetTriggerAxis(frc::XboxController::kLeftHand);

	double motorSpeed = rightOpTriggerAxis - leftOpTriggerAxis;

	//std::cout << "[ControlElevator] Motorspeed: '" << motorSpeed << "'.\n";

	SmartDashboard::PutNumber( "Elevator Motorspeed", motorSpeed );

	CommandBase::pElevator->SetMotorSpeed(motorSpeed);

	return;
}


bool ControlElevator::IsFinished()
{
	return false;
}



void ControlElevator::End()
{
	return;
}


void ControlElevator::Interrupted()
{
	return;
}



















