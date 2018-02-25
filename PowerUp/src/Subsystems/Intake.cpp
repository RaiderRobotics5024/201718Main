#include "Intake.h"
#include "../Utilities/Log.h"
#include "../Commands/Gripper.h"


Intake::Intake() : frc::Subsystem("Intake")
{
	LOG("[Intake] Constructed");

	this->pLeftMotor = new can::WPI_TalonSRX(INTAKE_LEFT_MOTOR_ID);
	this->pLeftMotor->SetInverted(true);

	this->pRightMotor = new can::WPI_TalonSRX(INTAKE_RIGHT_MOTOR_ID);

	this->pGripperSolenoid = new frc::DoubleSolenoid( GRIPPER_SOLENOID_CAN_ID,
	                                                  GRIPPER_SOLENOID_FORWARDCHANNEL_ID,
													  GRIPPER_SOLENOID_REVERSECHANNEL_ID );

	return;
}


Intake::~Intake()
{
	delete this->pLeftMotor;
	delete this->pRightMotor;
	delete this->pGripperSolenoid;

	return;
}


void Intake::OpenCloseIntake(void)
{
	frc::XboxController* pJoyDrive = CommandBase::pOI->GetJoystickDrive();


	if ( pJoyDrive->GetAButton() )
	{
		//close grippers
		this->pGripperSolenoid->Set(frc::DoubleSolenoid::Value::kForward);
	}
	else if ( pJoyDrive->GetBButton() )
	{
		// open gripper
		this->pGripperSolenoid->Set(frc::DoubleSolenoid::Value::kReverse);
	}

	return;
}


//static
const double Intake::SPEED_ADJUSTMENT_RATIO = 0.75;


void Intake::BeltIntake(void)
{
	frc::XboxController* pJoyDrive = CommandBase::pOI->GetJoystickDrive();

	double inSpeed = pJoyDrive->GetTriggerAxis(frc::XboxController::kLeftHand);
	double outSpeed = pJoyDrive->GetTriggerAxis(frc::XboxController::kRightHand);

	double Speed = inSpeed - outSpeed;

	Speed = Speed * Intake::SPEED_ADJUSTMENT_RATIO;

	this->pLeftMotor->Set(Speed);
	this->pRightMotor->Set(Speed);

	return;
}


void Intake::InitDefaultCommand()
{
	LOG("[Intake] Initialized Default Command");

	SetDefaultCommand( new Gripper() );

	return;
}


void Intake::Reset()
{
	LOG("[Intake] Resetting the motors");

	this->pLeftMotor->Set(0.0);
	this->pRightMotor->Set(0.0);

	return;
}
