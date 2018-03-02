#include "ClimbSystem.h"
#include "../Utilities/Log.h"
#include "../Commands/ClimbScale.h"

/**
 *
 */
ClimbSystem::ClimbSystem() : frc::Subsystem("ClimbSystem")
{
	LOG("[ClimbSystem] Constructed");

	this->pClimbMotor = new can::WPI_TalonSRX(CLIMBSYSTEM_MOTOR_ID);
	this->pClimbSolenoid = new frc::Solenoid( CLIMBSYSTEM_SOLENOID_CAN_ID,
	                                          CLIMBSYSTEM_SOLENOID_FORWARD_CHANNEL_ID );

	return;
}

/**
 *
 */
ClimbSystem::~ClimbSystem()
{
	delete this->pClimbMotor;
	delete this->pClimbSolenoid;

	return;
}

/**
 *
 */
void ClimbSystem::InitDefaultCommand()
{
	LOG("[ClimbSystem] Initilized Default Command");

	SetDefaultCommand(new ClimbScale());

	return;
}

/**
 *
 */
void ClimbSystem::ExtendArm(bool bOn)
{
	this->pClimbSolenoid->Set(bOn);

	return;
}

/**
 *
 */
void ClimbSystem::RetractArm(double dSpeed)
{
	this->pClimbMotor->Set(dSpeed);

	return;
}
