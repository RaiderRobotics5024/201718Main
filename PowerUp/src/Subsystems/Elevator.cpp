#include "Elevator.h"
#include <iostream>


Elevator::Elevator() : frc::Subsystem("Elevator")
{
	std::cout << "[Elevator] Constructed" << std::endl;

	this->pElevatorMotor = new can::WPI_TalonSRX(ELEVATOR_MOTOR_ID);

	return;
}

Elevator::~Elevator()
{
	delete this->pElevatorMotor;

	return;
}



void Elevator::InitDefaultCommand()
{
	std::cout << "[Elevator] Initialized Default Command" << std::endl;

	// What should the default command be here?
	//SetDefaultCommand(new XXX());

	return;
}


void Elevator::Reset()
{
	std::cout << "[Elevator] Resetting the motors" << std::endl;

	this->pElevatorMotor->Set(ControlMode::PercentOutput, 0.0);

	return;
}


