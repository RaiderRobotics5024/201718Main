#include "DriveTrain.h"
#include "../Commands/DriveWithJoystick.h"

/**
 *
 */

DriveTrain::DriveTrain() : frc::Subsystem("DriveTrain")
{
	std::cout << "[DriveTrain] Constructed" << std::endl;

	this->pLeftFrontMotor = new can::WPI_TalonSRX(LEFT_FRONT_MOTOR_ID);
	this->pLeftRearMotor = new can::WPI_TalonSRX(LEFT_REAR_MOTOR_ID);
	this->pLeftSpeedControllerGroup = new frc::SpeedControllerGroup(*pLeftFrontMotor, *pLeftRearMotor);

	this->pRightFrontMotor = new can::WPI_TalonSRX(RIGHT_FRONT_MOTOR_ID);
	this->pRightRearMotor = new can::WPI_TalonSRX(RIGHT_REAR_MOTOR_ID);
	this->pRightSpeedControllerGroup = new frc::SpeedControllerGroup(*pRightFrontMotor, *pRightRearMotor);

	this->pRobotDrive = new frc::DifferentialDrive(*pLeftSpeedControllerGroup, *pRightSpeedControllerGroup);

	pRobotDrive->SetSafetyEnabled(false);
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
}

/**
 *
 */

void DriveTrain::InitDefaultCommand()
{
	std::cout << "[DriveTrain] Initialized Default Command" << std::endl;

	SetDefaultCommand(new DriveWithJoystick());
}

/**
 *
 */

can::WPI_TalonSRX* DriveTrain::GetMotor()
{
	return this->pLeftFrontMotor;
}

// Put methods for controlling this subsystem here.
// Call these from Commands.

void DriveTrain::Drive(XboxController* joystick)
{
	double forwardSpeed = joystick->GetY(XboxController::kLeftHand);
	double turnAngle = joystick->GetX(XboxController::kLeftHand);

	pRobotDrive->ArcadeDrive(forwardSpeed, turnAngle);
}
