#include "Intake.h"
#include "../Utilities/Log.h"
#include "../Commands/ControlIntake.h"

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

	SetDefaultCommand(new ControlIntake());

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
void Intake::CloseGripper(void)
{
	this->pGripperSolenoid->Set(frc::DoubleSolenoid::Value::kForward);

	return;
}

/**
 *
 */
void Intake::OpenGripper(void)
{
	this->pGripperSolenoid->Set(frc::DoubleSolenoid::Value::kReverse);

	return;
}

/**
 *
 */
void Intake::SetSpeed(double dSpeed)
{
	this->pLeftMotor->Set(dSpeed);

	return;
}
