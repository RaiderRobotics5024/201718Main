#include "Elevator.h"
#include "ElevatorMap.h"
#include "../Utilities/Log.h"
#include "../Commands/ControlElevator.h"

// Define our global variable to set elevator height
ElevatorHeight gElevatorHeight = BOTTOM;

/**
 *
 */
Elevator::Elevator() : frc::Subsystem("Elevator")
{
	LOG("[Elevator] Constructed");

	this->pElevatorMotor = new can::WPI_TalonSRX(ELEVATOR_MOTOR_ID);
	this->pElevatorMotor->SetNeutralMode(NeutralMode::Brake);


	this->pTopSwitch    = new frc::DigitalInput(ELEVATOR_TOP_SWITCH_ID);
	this->pMiddleSwitch = new frc::DigitalInput(ELEVATOR_MID_SWITCH_ID);
	this->pBottomSwitch = new frc::DigitalInput(ELEVATOR_BOTTOM_SWITCH_ID);

	return;
}

/**
 *
 */
Elevator::~Elevator()
{
	LOG("[Elevator] Destroyed");

	delete this->pElevatorMotor;

	delete this->pTopSwitch;
	delete this->pMiddleSwitch;
	delete this->pBottomSwitch;

	return;
}

/**
 *
 */
void Elevator::InitDefaultCommand()
{
	LOG("[Elevator] Initialized Default Command");

	SetDefaultCommand(new ControlElevator());

	return;
}

/**
 *
 */
bool Elevator::IsTopSwitchAligned()
{
	// the Get returns 1 if magnets are not aligned, 0 if magnets are aligned
	// so we return the opposite of the Get
	return !this->pTopSwitch->Get();
}

/**
 *
 */
bool Elevator::IsMiddleSwitchAligned()
{
	// the Get returns 1 if magnets are not aligned, 0 if magnets are aligned
	// so we return the opposite of the Get
	return !this->pMiddleSwitch->Get();
}

/**
 *
 */
bool Elevator::IsBottomSwitchAligned()
{
	// the Get returns 1 if magnets are not aligned, 0 if magnets are aligned
	// so we return the opposite of the Get
	return !this->pBottomSwitch->Get();
}

/**
 *
 */
void Elevator::Reset()
{
	LOG("[Elevator] Resetting");

	this->pElevatorMotor->Set(0.0);

	return;
}

/**
 *
 */
void Elevator::SetMotorSpeed(double dSpeed)
{
	this->pElevatorMotor->Set(dSpeed);

	return;
}
