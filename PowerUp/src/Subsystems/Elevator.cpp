#include "Elevator.h"
#include <iostream>
#include "../Commands/ControlElevator.h"

Elevator::Elevator() : frc::Subsystem("Elevator")
{
	std::cout << "[Elevator] Constructed" << std::endl;

	this->pElevatorMotor = new can::WPI_TalonSRX(ELEVATOR_MOTOR_ID);
	this->pTopElevatorSwitch = new frc::DigitalInput(ELEVATOR_TOP_SWITCH_ID);
	this->pMidElevatorSwitch = new frc::DigitalInput(ELEVATOR_MID_SWITCH_ID);
	this->pBottomElevatorSwitch = new frc::DigitalInput(ELEVATOR_BOTTOM_SWITCH_ID);
	return;
}

Elevator::~Elevator()
{
	delete this->pElevatorMotor;

	return;
}

void Elevator::SetMotorSpeed(double elevatorSpeed)
{
	this->pElevatorMotor->Set(elevatorSpeed);

	return;
}


void Elevator::InitDefaultCommand()
{
	std::cout << "[Elevator] Initialized Default Command" << std::endl;

	// What should the default command be here?
	SetDefaultCommand(new ControlElevator());

	return;
}


void Elevator::Reset()
{
	std::cout << "[Elevator] Resetting the motors" << std::endl;

	this->pElevatorMotor->Set(0.0);

	return;
}


