#include "Gripper.h"
#include "../Utilities/Log.h"
#include <math.h>
#include "../RobotMap.h"

/**
 *
 */
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

/**
 *
 */
void Gripper::Initialize()
{
	LOG("[Gripper] Initialize");

	return;
}

/**
 *
 */
void Gripper::Execute()
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
bool Gripper::IsFinished()
{
	return false;
}

/**
 *
 */
void Gripper::End()
{
	LOG("[Gripper] Ended");

	return;
}

/**
 *
 */
void Gripper::Interrupted()
{
	LOG("[Gripper] Interrupted");

	return;
}
