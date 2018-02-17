#include "ControlElevator.h"

ControlElevator::ControlElevator() {
	std::cout << "[ControlElevator] Constructed" << std::endl;

	if (CommandBase::pElevator != nullptr)
	{
		Requires(CommandBase::pElevator);
	}
	else
	{
		std::cout << "[ControlElevator] elevator is null!" << std::endl;
	}
	return;
}

void ControlElevator::Initialize() {
	std::cout << "[ControlElevator] Constructed" << std::endl;
	return;
}

void ControlElevator::Execute() {
	double rightOpTriggerAxis = CommandBase::pOI->GetJoystickOperator()->GetTriggerAxis(XboxController::kRightHand);
	double leftOpTriggerAxis = CommandBase::pOI->GetJoystickOperator()->GetTriggerAxis(XboxController::kLeftHand);
	double motorSpeed = rightOpTriggerAxis - leftOpTriggerAxis;
	std::cout << "[ControlElevator] Motorspeed: '" << motorSpeed << "'.\n" ;
	CommandBase::pElevator->SetMotorSpeed(motorSpeed);
}


// Make this return true when this Command no longer needs to run execute()
bool ControlElevator::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ControlElevator::End() {
	return;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ControlElevator::Interrupted() {
	return;
}
