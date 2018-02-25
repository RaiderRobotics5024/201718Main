#include "Elevator.h"
#include "../Utilities/Log.h"
#include "../Commands/ControlElevator.h"


Elevator::Elevator() : frc::Subsystem("Elevator")
{
	LOG("[Elevator] Constructed");

	this->pElevatorMotor = new can::WPI_TalonSRX(ELEVATOR_MOTOR_ID);
	this->pTopElevatorSwitch = new frc::DigitalInput(ELEVATOR_TOP_SWITCH_ID);
	this->pMidElevatorSwitch = new frc::DigitalInput(ELEVATOR_MID_SWITCH_ID);
	this->pBottomElevatorSwitch = new frc::DigitalInput(ELEVATOR_BOTTOM_SWITCH_ID);

	return;
}


Elevator::~Elevator()
{
	delete this->pElevatorMotor;
	delete this->pTopElevatorSwitch;
	delete this->pMidElevatorSwitch;
	delete this->pBottomElevatorSwitch;

	return;

}


void Elevator::SetMotorSpeed(double elevatorSpeed)
{
	this->pElevatorMotor->Set(elevatorSpeed);

	return;
}


void Elevator::InitDefaultCommand()
{
	LOG("[Elevator] Initilizaed Default Cmomand");

	SetDefaultCommand( new ControlElevator() );

	return;
}


void Elevator::Reset()
{
	LOG("[Elevator] Resettign the motors");

	this->pElevatorMotor->Set(0.0);

	return;
}