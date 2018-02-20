#include "ClimbSystem.h"
#include "../Utilities/Log.h"

/**
 *
 */

ClimbSystem::ClimbSystem() : frc::Subsystem("ClimbSystem")
{
	LOG("[ClimbSystem] Constructed");

	this->pClimbMotor = new can::WPI_TalonSRX(CLIMBSYSTEM_MOTOR_ID);
	this->pClimbSolenoid = new frc::DoubleSolenoid(CLIMBSYSTEM_SOLENOID_CAN_ID, CLIMBSYSTEM_SOLENOID_FORWARD_CHANNEL_ID, CLIMBSYSTEM_SOLENOID_REVERSE_CHANNEL_ID);

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
	LOG("[ClimbSystem] Initialized Default Command");

	return;
}

/**
 *
 */

void ClimbSystem::ExtendArm()
{
	this->pClimbSolenoid->Set(frc::DoubleSolenoid::Value::kForward);

	return;
}

/**
 *
 */

void ClimbSystem::RetractArm()
{
	this->pClimbMotor->Set(1.0);

	return;
}
