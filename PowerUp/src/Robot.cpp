#include "Robot.h"

/**
 *
 */

Robot::Robot()
{
	SmartDashboard::init();

	this->motor_id = 1;
	this->motor_speed = 0.0;
	SetMotor(motor_id);

	this->pXboxController = new XboxController(0);
}

/**
 *
 */

Robot::~Robot()
{
	delete this->pXboxController;
	delete this->pTalonSRX;
}

/**
 *
 */

void Robot::SetMotor(int motor_id)
{
	if (this->pTalonSRX != nullptr)
	{
		this->pTalonSRX->Set(ControlMode::PercentOutput, 0);
		delete this->pTalonSRX;
	}

	this->pTalonSRX = new WPI_TalonSRX(motor_id);
	this->pTalonSRX->SetInverted(false);
	this->pTalonSRX->SetSensorPhase(true);
}

/**
 *
 */

void Robot::TeleopPeriodic()
{
	SmartDashboard::PutNumber("Motor ID", motor_id);

	if (pXboxController->GetBumperPressed(XboxController::kLeftHand)) {
		motor_id = (motor_id > 1) ? motor_id-- : 1;
		SetMotor(motor_id);
	} else if (pXboxController->GetBumperPressed(XboxController::kRightHand)) {
		motor_id = (motor_id < 8) ? motor_id++ : 8;
		SetMotor(motor_id);
	}

	if (this->pXboxController->GetXButton()) {
		this->pTalonSRX->SetInverted(false);
	} else if (this->pXboxController->GetBButton()) {
		this->pTalonSRX->SetInverted(true);
	}

	if (this->pXboxController->GetYButton()) {
		motor_speed = 1.0;
	} else if (this->pXboxController->GetAButton()) {
		motor_speed = -1.0;
	} else {
		motor_speed = 0.0;
	}

	pTalonSRX->Set(motor_speed);

}

START_ROBOT_CLASS(Robot)
