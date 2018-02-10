#include "Intake.h"
#include <iostream>


Intake::Intake() : frc::Subsystem("Intake")
{
	std::cout << "[Intake] Constructed" << std::endl;

	this->pLeftMotor = new can::WPI_TalonSRX(INTAKE_LEFT_MOTOR_ID);
	this->pRightMotor = new can::WPI_TalonSRX(INTAKE_RIGHT_MOTOR_ID);

	return;
}

Intake::~Intake()
{
	delete this->pLeftMotor;
	delete this->pRightMotor;

	return;
}
void Intake::InitDefaultCommand()
{
	std::cout << "[Intake] Initialized Default Command" << std::endl;

	// What should the default command be here?
	//SetDefaultCommand(new XXX());

	return;
}


void Intake::Reset()
{
	std::cout << "[DriveTrain] Resetting the motors" << std::endl;

	this->pLeftMotor->Set(ControlMode::PercentOutput, 0.0);
	this->pRightMotor->Set(ControlMode::PercentOutput, 0.0);

	return;
}


