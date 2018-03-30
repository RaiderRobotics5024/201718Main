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
	double leftOpTriggerAxis  = pJoyOperator->GetTriggerAxis(frc::XboxController::kLeftHand);

	double dMotorSpeed = rightOpTriggerAxis - leftOpTriggerAxis;

	if (CommandBase::pElevator->IsTopSwitchAligned() && dMotorSpeed > 0.0)
	{
		dMotorSpeed = 0; // don't let the motor go passed the top switch
	}

	CommandBase::pElevator->SetMotorSpeed(dMotorSpeed);

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

	CommandBase::pElevator->Reset();

	return;
}

/**
 *
 */
void ControlElevator::Interrupted()
{
	LOG("[ControlElevator] Interrupted" );

	CommandBase::pElevator->Reset();

	return;
}

/**
 *
 */
void ControlElevator::Trace(double dMotorSpeed)
{
	if (iCounter++ == 10)
	{
		SmartDashboard::PutNumber( "Elevator Motorspeed", dMotorSpeed );

		LOG("[ControlElevator] Switch: " << CommandBase::pElevator->IsTopSwitchAligned() << " Speed: " << dMotorSpeed);

		iCounter = 0;
	}

	return;
}
