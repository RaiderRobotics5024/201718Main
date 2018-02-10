#include "DriveTrain.h"
#include "../Commands/DriveWithJoystick.h"

/**
 *
 */

DriveTrain::DriveTrain() : frc::Subsystem("DriveTrain")
{
	std::cout << "[DriveTrain] Constructed" << std::endl;

	this->pLeftFrontMotor = new can::WPI_TalonSRX(DRIVETRAIN_LEFT_FRONT_MOTOR_ID);
	this->pLeftRearMotor = new can::WPI_TalonSRX(DRIVETRAIN_LEFT_REAR_MOTOR_ID);
	this->pLeftSpeedControllerGroup
	                = new frc::SpeedControllerGroup( *(this->pLeftFrontMotor),
			                                         *(this->pLeftRearMotor) );

	this->pRightFrontMotor = new can::WPI_TalonSRX(DRIVETRAIN_RIGHT_FRONT_MOTOR_ID);
	this->pRightRearMotor = new can::WPI_TalonSRX(DRIVETRAIN_RIGHT_REAR_MOTOR_ID);
	this->pRightSpeedControllerGroup
	                = new frc::SpeedControllerGroup( *(this->pRightFrontMotor),
                                                     *(this->pRightRearMotor) );

	this->pRobotDrive
	                = new frc::DifferentialDrive( *(this->pLeftSpeedControllerGroup),
                                                  *(this->pRightSpeedControllerGroup) );

	pRobotDrive->SetSafetyEnabled(false);

	return;
}

/**
 *
 */

DriveTrain::~DriveTrain()
{
	delete this->pRobotDrive;
	delete this->pRightSpeedControllerGroup;
	delete this->pLeftSpeedControllerGroup;
	delete this->pRightFrontMotor;
	delete this->pRightRearMotor;
	delete this->pLeftFrontMotor;
	delete this->pLeftRearMotor;

	return;
}

/**
 *
 */

void DriveTrain::InitDefaultCommand()
{
	std::cout << "[DriveTrain] Initialized Default Command" << std::endl;

	SetDefaultCommand(new DriveWithJoystick());

	return;
}

/**
 *
 */

// Put methods for controlling this subsystem here.
// Call these from Commands.

void DriveTrain::Drive(XboxController* pJoystick)
{
	double forwardSpeed = pJoystick->GetY(XboxController::kLeftHand);
	double turnAngle = pJoystick->GetX(XboxController::kLeftHand);

	this->pRobotDrive->ArcadeDrive(forwardSpeed, turnAngle);

	return;
}

void DriveTrain::ArcadeDrive( double xSpeed, double zRotation )
{
	// Taken from DriveTrain::Drive()
	this->pRobotDrive->ArcadeDrive(xSpeed, zRotation);

	return;
}

void DriveTrain::CurvatureDrive( double xSpeed, double zRotation, bool isQuickTurn )
{
	this->pRobotDrive->CurvatureDrive( xSpeed, zRotation, isQuickTurn );

	return;
}

void DriveTrain::TankDrive( double leftSpeed, double rightSpeed )
{
	this->pRobotDrive->TankDrive( leftSpeed, rightSpeed );

	return;
}


void DriveTrain::Reset()
{
	std::cout << "[DriveTrain] Resetting the motors" << std::endl;

	this->pLeftFrontMotor->Set(ControlMode::PercentOutput, 0.0);
	this->pLeftRearMotor->Set(ControlMode::PercentOutput, 0.0);
	this->pRightFrontMotor->Set(ControlMode::PercentOutput, 0.0);
	this->pRightRearMotor->Set(ControlMode::PercentOutput, 0.0);

	return;
}













