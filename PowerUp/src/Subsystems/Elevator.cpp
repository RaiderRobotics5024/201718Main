#include "Elevator.h"
#include "../Utilities/Log.h"
#include "../Commands/ControlElevator.h"

/**
 *
 */
Elevator::Elevator() : frc::Subsystem("Elevator")
{
	LOG("[Elevator] Constructed");

	this->pElevatorMotor = new can::WPI_TalonSRX(ELEVATOR_MOTOR_ID);

	this->pTopSwitch    = new frc::DigitalInput(ELEVATOR_TOP_SWITCH_ID);
	this->pMiddleSwitch = new frc::DigitalInput(ELEVATOR_MID_SWITCH_ID);
	this->pBottomSwitch = new frc::DigitalInput(ELEVATOR_BOTTOM_SWITCH_ID);

	this->pTopCounter    = new Counter(pTopSwitch);
	this->pMiddleCounter = new Counter(pMiddleSwitch);
	this->pBottomCounter = new Counter(pBottomSwitch);

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

	delete this->pTopCounter;
	delete this->pMiddleCounter;
	delete this->pBottomCounter;

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
void Elevator::Reset()
{
	this->pElevatorMotor->Set(0.0);

	return;
}

/**
 *
 */
void Elevator::ResetCounters()
{
	this->pTopCounter->Reset();
	this->pMiddleCounter->Reset();
	this->pBottomCounter->Reset();
}

/**
 *
 */
bool Elevator::IsTopSwitchAligned()
{
	// the Get returns 1 if magnets are not aligned, 0 if magnets are aligned
	// so we return the opposite of the Get
	return this->pTopCounter->Get() > 0;
}

/**
 *
 */
bool Elevator::IsMiddleSwitchAligned()
{
	// the Get returns 1 if magnets are not aligned, 0 if magnets are aligned
	// so we return the opposite of the Get
	return this->pMiddleCounter->Get() > 0;
}

/**
 *
 */
bool Elevator::IsBottomSwitchAligned()
{
	// the Get returns 1 if magnets are not aligned, 0 if magnets are aligned
	// so we return the opposite of the Get
	return this->pBottomCounter->Get() > 0;
}

/**
 *
 */
void Elevator::SetMotorSpeed(double dSpeed)
{
	this->pElevatorMotor->Set(dSpeed);

	return;
}
