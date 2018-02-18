#include "BotClimb.h"
#include <iostream>


BotClimb::BotClimb() : frc::Subsystem("BotClimb")
{
	std::cout << "[BotClimb] Constructed" << std::endl;

	this->pClimbMotor = new can::WPI_TalonSRX(INTAKE_LEFT_MOTOR_ID);


	return;
}

BotClimb::~BotClimb()
{
	delete this->pClimbMotor;

	return;
}


void BotClimb::InitDefaultCommand()
{
	std::cout << "[BotClimb] Initialized Default Command" << std::endl;

	// What should the default command be here?
	//SetDefaultCommand(new XXX());

	return;
}


void BotClimb::Reset()
{
	std::cout << "[BotClimb] Resetting the motors" << std::endl;

	this->pClimbMotor->Set(ControlMode::PercentOutput, 0.0);

	return;
}


