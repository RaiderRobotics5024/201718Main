#include "ControlElevator.h"
#include "../Utilities/Log.h"

ControlElevator::ControlElevator()
{
	LOG("[ControlElevator] Constructed");

	if ( CommandBase::pElevator != nullptr )
	{
		Requires(CommandBase::pElevator);
	}
	else
	{
		LOG("[ControlElevator] elevator is NULL!");
	}

	return;
}


void ControlElevator::Initialize()
{
	LOG("[ControlElevator] Constructed");

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



















