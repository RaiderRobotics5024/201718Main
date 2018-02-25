#include "ClimbSystem.h"
#include "../Utilities/Log.h"

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

	return;
}

/**
 *
 */
void ClimbSystem::ExtendArm(void)
{
	this->pClimbSolenoid->Set(true);

	return;
}

/**
 *
 */
void ClimbSystem::RetractArm(void)
{
	this->pClimbMotor->Set(1.0);

	return;
}
