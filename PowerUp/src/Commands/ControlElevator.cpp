#include "ControlElevator.h"
#include "../Utilities/Log.h"

/**
 *
 */
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

	CommandBase::pElevator->ResetCounters();

	return;
}

/**
 *
 */
void ControlElevator::Initialize()
{
	LOG("[ControlElevator] Initalized");

	return;
}

/**
 *
 */
void ControlElevator::Execute()
{
	frc::XboxController* pJoyOperator = CommandBase::pOI->GetJoystickOperator();

	double rightOpTriggerAxis = pJoyOperator->GetTriggerAxis(frc::XboxController::kRightHand);
	double leftOpTriggerAxis = pJoyOperator->GetTriggerAxis(frc::XboxController::kLeftHand);

	double dMotorSpeed = rightOpTriggerAxis - leftOpTriggerAxis;

	LOG("[ControlElevator] Switch: " << CommandBase::pElevator->IsTopSwitchAligned() << " Speed: " << dMotorSpeed);

	if (CommandBase::pElevator->IsTopSwitchAligned() && dMotorSpeed > 0.0)
	{
		LOG("[ControlElevator] At the top" );

		dMotorSpeed = 0; // don't let the motor go passed the top switch
		CommandBase::pElevator->ResetCounters();
	}

	CommandBase::pElevator->SetMotorSpeed(dMotorSpeed);

	if (iCounter++ == 10)
	{
		SmartDashboard::PutNumber( "Elevator Motorspeed", dMotorSpeed );

		iCounter = 0;
	}

	return;
}

/**
 *
 */
bool ControlElevator::IsFinished()
{
	return false;
}

/**
 *
 */
void ControlElevator::End()
{
	LOG("[ControlElevator] Ended");

	return;
}

/**
 *
 */
void ControlElevator::Interrupted()
{
	LOG("[ControlElevator] Interrupted" );

	return;
}
