#include "ControlGripper.h"
#include "../Utilities/Log.h"
#include <math.h>
#include "../RobotMap.h"

/**
 *
 */
ControlGripper::ControlGripper()
{
	LOG("[ControlGripper] Constructed");

	if ( CommandBase::pIntake != nullptr )
	{
		Requires(CommandBase::pIntake);
	}
	else
	{
		LOG("[ControlGripper] intake is NULL!");
	}

	return;
}

/**
 *
 */
void ControlGripper::Initialize()
{
	LOG("[ControlGripper] Initialize");

	return;
}

/**
 *
 */
void ControlGripper::Execute()
{
	frc::XboxController* pJoyDrive = CommandBase::pOI->GetJoystickDrive();

	double dInSpeed  = pJoyDrive->GetTriggerAxis(frc::XboxController::kLeftHand);
	double dOutSpeed = pJoyDrive->GetTriggerAxis(frc::XboxController::kRightHand);

	double dSpeed = (dInSpeed - dOutSpeed) * GRIPPER_SPEED_ADJUSTMENT_RATIO;
	CommandBase::pIntake->SetSpeed(dSpeed);

	if (pJoyDrive->GetAButton())
	{
		CommandBase::pIntake->CloseGripper();
	}
	else if ( pJoyDrive->GetBButton() )
	{
		CommandBase::pIntake->OpenGripper();
	}

	return;
}

/**
 *
 */
bool ControlGripper::IsFinished()
{
	return false;
}

/**
 *
 */
void ControlGripper::End()
{
	LOG("[ControlGripper] Ended");

	return;
}

/**
 *
 */
void ControlGripper::Interrupted()
{
	LOG("[Gripper] Interrupted");

	return;
}
