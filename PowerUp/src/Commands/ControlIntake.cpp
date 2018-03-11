#include "ControlIntake.h"
#include "../Utilities/Log.h"
#include <math.h>
#include "../RobotMap.h"

/**
 *
 */
ControlIntake::ControlIntake()
{
	LOG("[ControlIntake] Constructed");

	if ( CommandBase::pIntake != nullptr )
	{
		Requires(CommandBase::pIntake);
	}
	else
	{
		LOG("[ControlIntake] intake is NULL!");
	}

	return;
}

/**
 *
 */
void ControlIntake::Initialize()
{
	LOG("[ControlIntake] Initialize");

	return;
}

/**
 *
 */
void ControlIntake::Execute()
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
bool ControlIntake::IsFinished()
{
	return false;
}

/**
 *
 */
void ControlIntake::End()
{
	LOG("[ControlIntake] Ended");

	return;
}

/**
 *
 */
void ControlIntake::Interrupted()
{
	LOG("[ControlIntake] Interrupted");

	return;
}
