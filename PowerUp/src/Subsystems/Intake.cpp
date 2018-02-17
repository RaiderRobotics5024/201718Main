#include "Intake.h"
#include <iostream>
#include "../Commands/Gripper.h"


Intake::Intake() : frc::Subsystem("Intake")
{
	std::cout << "[Intake] Constructed" << std::endl;

	this->pLeftMotor = new can::WPI_TalonSRX(INTAKE_LEFT_MOTOR_ID);
	this->pRightMotor = new can::WPI_TalonSRX(INTAKE_RIGHT_MOTOR_ID);


	this->pGripperSolenoid = new frc::DoubleSolenoid( GRIPPER_SOLENOID_CAN_ID,
													  GRIPPER_SOLENOID_FORWARDCHANNEL_ID,
	                                                  GRIPPER_SOLENOID_REVERSECHANNEL_ID );
	//this->pGripperSolenoid->Set(DoubleSolenoid::kOff);


	return;
}

Intake::~Intake()
{
	delete this->pLeftMotor;
	delete this->pRightMotor;

	delete this->pGripperSolenoid;

	return;
}
/*
void Intake::SetMotorSpeed(double Speed)
{
	this->pLeftMotor->Set(Speed);
	this->pRightMotor->Set(Speed);
	return;
}
*/
//takes kOff, kForward, or kReverse

void Intake::OpenCloseIntake()
{

    //this->pGripperSolenoid->Set(frc::DoubleSolenoid::Value::kForward);
    if (CommandBase::pOI->GetJoystickDrive()->GetAButton())
    	{
    	       //close grippers
    	this->pGripperSolenoid->Set(frc::DoubleSolenoid::Value::kForward);

    	} else if(CommandBase::pOI->GetJoystickDrive()->GetBButton())
    	{
    	       //open gripper
    		this->pGripperSolenoid->Set(frc::DoubleSolenoid::Value::kReverse);

    	 };

	return;
}

void Intake::BeltIntake()
{
	double inSpeed = CommandBase::pOI->GetJoystickDrive()->GetTriggerAxis(XboxController::kLeftHand);
	double outSpeed = CommandBase::pOI->GetJoystickDrive()->GetTriggerAxis(XboxController::kRightHand);
	double Speed = inSpeed - outSpeed;
	this->pLeftMotor->Set(Speed);
	this->pRightMotor->Set(Speed*-1);
	return;
}
void Intake::InitDefaultCommand()
{
	std::cout << "[Intake] Initialized Default Command" << std::endl;

	SetDefaultCommand(new Gripper());

	return;
}


void Intake::Reset()
{
	std::cout << "[Intake] Resetting the motors" << std::endl;

	//this->pGripperSolenoid->Set(kOff);

	this->pLeftMotor->Set(ControlMode::PercentOutput, 0.0);
	this->pRightMotor->Set(ControlMode::PercentOutput, 0.0);

	return;
}


