#include "Intake.h"
#include "../Utilities/Log.h"
#include "../Commands/Gripper.h"

/**
 *
 */
Intake::Intake() : frc::Subsystem("Intake")
{
	LOG("[Intake] Constructed");

	this->pLeftMotor = new can::WPI_TalonSRX(INTAKE_LEFT_MOTOR_ID);
	this->pLeftMotor->SetInverted(true);

	this->pRightMotor = new can::WPI_TalonSRX(INTAKE_RIGHT_MOTOR_ID);
	this->pRightMotor->Follow(*pLeftMotor);

	this->pGripperSolenoid = new frc::DoubleSolenoid( GRIPPER_SOLENOID_CAN_ID, GRIPPER_SOLENOID_FORWARDCHANNEL_ID, GRIPPER_SOLENOID_REVERSECHANNEL_ID );

	return;
}

/**
 *
 */
Intake::~Intake()
{
	delete this->pLeftMotor;
	delete this->pRightMotor;
	delete this->pGripperSolenoid;

	return;
}

/**
 *
 */
void Intake::InitDefaultCommand()
{
	LOG("[Intake] Initialized Default Command");

	SetDefaultCommand(new Gripper());

	return;
}

/**
 *
 */
void Intake::Reset()
{
	LOG("[Intake] Resetting the motors");

	this->pLeftMotor->Set(0.0);

	return;
}

/**
 *
 */
void Intake::BeltIn(double speed)
{
	this->pLeftMotor->Set(-speed);

	return;
}

/**
 *
 */
void Intake::BeltIntake(void)
{
	frc::XboxController* pJoystick = CommandBase::pOI->GetJoystickDrive();

	double dInSpeed  = pJoystick->GetTriggerAxis(frc::XboxController::kLeftHand);
	double dOutSpeed = pJoystick->GetTriggerAxis(frc::XboxController::kRightHand);

	double dSpeed = dInSpeed - dOutSpeed;

	dSpeed = dSpeed * GRIPPER_SPEED_ADJUSTMENT_RATIO;

	this->pLeftMotor->Set(dSpeed);

	return;
}

/**
 *
 */
void Intake::BeltOff(void)
{
	this->pLeftMotor->Set(0.0);

	return;
}

/**
 *
 */
void Intake::BeltOut(double dSpeed)
{
	this->pLeftMotor->Set(dSpeed);

	return;
}

/**
 *
 */
void Intake::CloseGripper(void)
{
	this->pGripperSolenoid->Set(frc::DoubleSolenoid::Value::kForward);

	return;
}

/**
 *
 */
void Intake::OpenCloseIntake(void)
{
	frc::XboxController* pJoystick = CommandBase::pOI->GetJoystickDrive();

	if (pJoystick->GetAButton())
	{
		this->pGripperSolenoid->Set(frc::DoubleSolenoid::Value::kForward); // close grippers
	}
	else if ( pJoystick->GetBButton() )
	{
		this->pGripperSolenoid->Set(frc::DoubleSolenoid::Value::kReverse); // open grippers
	}

	return;
}
