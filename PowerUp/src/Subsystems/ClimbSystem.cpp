#include "ClimbSystem.h"


ClimbSystem::ClimbSystem() : frc::Subsystem("ClimbSystem")
{
	std::cout << "[ClimbSystem] Constructed" << std::endl;

	this->pClimbMotor = new can::WPI_TalonSRX(CLIMBSYSTEM_MOTOR_ID);
	this->pClimbSolenoid = new frc::Solenoid( CLIMBSYSTEM_SOLENOID_CAN_ID,
	                                          CLIMBSYSTEM_SOLENOID_FORWARD_CHANNEL_ID );

	return;
}


ClimbSystem::~ClimbSystem()
{
	delete this->pClimbMotor;
	delete this->pClimbSolenoid;

	return;
}


void ClimbSystem::InitDefaultCommand()
{
	std::cout << "[ClimbSystem] Initilized Default Command" << std::endl;

	return;
}


void ClimbSystem::ExtendArm(void)
{
	this->pClimbSolenoid->Set(frc::DoubleSolenoid::Value::kForward);

	return;
}


void ClimbSystem::RetractArm(void)
{
	this->pClimbMotor->Set(1.0);

	return;
}




