#include "DriveTrain.h"
#include <math.h>
#include "../Utilities/Log.h"
#include "../Commands/DriveWithJoystick.h"
#include "../RobotMap.h"

/**
 *
 */

DriveTrain::DriveTrain() : frc::Subsystem("DriveTrain")
{
	LOG("[DriveTrain] Constructed");

	this->pLeftFrontMotor = new can::WPI_TalonSRX(LEFT_FRONT_MOTOR_ID);
	this->pLeftRearMotor = new can::WPI_TalonSRX(LEFT_REAR_MOTOR_ID);
	this->pLeftRearMotor->Follow(*pLeftFrontMotor);

	this->pLeftFrontMotor->SetInverted(false);
	this->pLeftRearMotor->SetInverted(false);

	this->pRightFrontMotor = new can::WPI_TalonSRX(RIGHT_FRONT_MOTOR_ID);
	this->pRightRearMotor = new can::WPI_TalonSRX(RIGHT_REAR_MOTOR_ID);
	this->pRightRearMotor->Follow(*pRightRearMotor);

	this->pRightFrontMotor->SetInverted(true);
	this->pRightRearMotor->SetInverted(true);

	this->pRobotDrive = new frc::DifferentialDrive(*pLeftFrontMotor, *pRightFrontMotor);

	pRobotDrive->SetSafetyEnabled(false);

	this->pGyro = new AHRS(SPI::Port::kMXP);

	this->pTurnController = new PIDController(PID_P, PID_I, PID_D, PID_F, pGyro, this, 0.5);
	this->pTurnController->SetInputRange(-180.0f,  180.0f);
	this->pTurnController->SetOutputRange(-1.0, 1.0);
	this->pTurnController->SetAbsoluteTolerance(TOLERANCE_DEGREES);
	this->pTurnController->SetContinuous(true);

	this->dRotateToAngleRate = 0.0f;

	return;
}

/**
 *
 */

DriveTrain::~DriveTrain()
{
	delete this->pRobotDrive;
	delete this->pRightFrontMotor;
	delete this->pRightRearMotor;
	delete this->pLeftFrontMotor;
	delete this->pLeftRearMotor;

	delete this->pGyro;

	return;
}

/**
 *
 */

void DriveTrain::InitAutonomous(bool inverted)
{
	LOG("[DriveTrain] Autonomous Initialized");

	int absolutePosition = pLeftFrontMotor->GetSelectedSensorPosition(0) & 0xFFF; /* mask out the bottom12 bits, we don't care about the wrap arounds */
	/* use the low level API to set the quad encoder signal */
	pLeftFrontMotor->SetSelectedSensorPosition(absolutePosition, PID_LOOP_INDEX, TIMEOUT_MS);

	/* choose the sensor and sensor direction */
	pLeftFrontMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, PID_LOOP_INDEX, TIMEOUT_MS);
	pLeftFrontMotor->SetSensorPhase(true);

	/* set the peak and nominal outputs, 12V means full */
	pLeftFrontMotor->ConfigNominalOutputForward(0, TIMEOUT_MS);
	pLeftFrontMotor->ConfigNominalOutputReverse(0, TIMEOUT_MS);
	pLeftFrontMotor->ConfigPeakOutputForward(1, TIMEOUT_MS);
	pLeftFrontMotor->ConfigPeakOutputReverse(-1, TIMEOUT_MS);

	/* set closed loop gains in slot0 */
	pLeftFrontMotor->Config_kF(PID_LOOP_INDEX, 0.0, TIMEOUT_MS);
	pLeftFrontMotor->Config_kP(PID_LOOP_INDEX, 0.1, TIMEOUT_MS);
	pLeftFrontMotor->Config_kI(PID_LOOP_INDEX, 0.0, TIMEOUT_MS);
	pLeftFrontMotor->Config_kD(PID_LOOP_INDEX, 0.0, TIMEOUT_MS);

	pRightFrontMotor->Follow(*pLeftFrontMotor);
	pRightFrontMotor->SetInverted(inverted);

	return;
}

/**
 *
 */

void DriveTrain::InitDefaultCommand()
{
	LOG("[DriveTrain] Initialized Default Command");

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
	double drivingSpeed = pJoystick->GetY(XboxController::kLeftHand);
	double turningSpeed = pJoystick->GetX(XboxController::kLeftHand);

	if (fabs(drivingSpeed) <= XBOX_DEADZONE_LEFT_JOY)
	{
		drivingSpeed = 0.0;
	}

	if (fabs(turningSpeed) <= XBOX_DEADZONE_LEFT_JOY)
	{
		turningSpeed = 0.0;
	}

	this->pRobotDrive->ArcadeDrive(drivingSpeed, turningSpeed);

	return;
}

/**
 *
 */

void DriveTrain::Drive(double targetPositionRotations)
{
	pLeftFrontMotor->Set(ControlMode::Position, targetPositionRotations);

	return;
}

/**
 *
 */

void DriveTrain::ArcadeDrive(double drivingSpeed, double turningSpeed)
{
	this->pRobotDrive->ArcadeDrive(drivingSpeed, turningSpeed);

	return;
}

void DriveTrain::CurvatureDrive(double xSpeed, double zRotation, bool isQuickTurn)
{
	this->pRobotDrive->CurvatureDrive(xSpeed, zRotation, isQuickTurn);

	return;
}

void DriveTrain::TankDrive(double leftSpeed, double rightSpeed)
{
	this->pRobotDrive->TankDrive(leftSpeed, rightSpeed);

	return;
}

/**
 *
 */

double DriveTrain::GetAngle()
{
	return pGyro->GetAngle();
}

/**
 *
 */

double DriveTrain::GetPosition()
{
	return pLeftFrontMotor->GetSelectedSensorPosition(SLOT_INDEX);
}

/**
 *
 */

bool DriveTrain::IsDriving()
{
	return pLeftFrontMotor->Get() != 0;
}

/**
 *
 */

bool DriveTrain::IsTurning()
{
	return pLeftFrontMotor->Get() != 0;
}

/**
 *
 */

void DriveTrain::ResetDrive()
{
	LOG("[DriveTrain] Resetting the motors");

	this->pLeftFrontMotor->Set(ControlMode::PercentOutput, 0);
	this->pLeftRearMotor->Set(ControlMode::PercentOutput, 0);
	this->pRightFrontMotor->Set(ControlMode::PercentOutput, 0);
	this->pRightRearMotor->Set(ControlMode::PercentOutput, 0);

	this->pLeftRearMotor->Follow(*pLeftFrontMotor);
	this->pLeftFrontMotor->SetInverted(false);
	this->pLeftRearMotor->SetInverted(false);

	this->pRightRearMotor->Follow(*pRightRearMotor);
	this->pRightFrontMotor->SetInverted(true);
	this->pRightRearMotor->SetInverted(true);

	return;
}

/**
 *
 */

void DriveTrain::ResetGyro()
{
	LOG("[DriveTrain] Resetting the gyro");

	pGyro->ZeroYaw();

	return;
}

/**
 *
 */

void DriveTrain::Turn(double setpoint)
{
    this->pTurnController->SetSetpoint(setpoint);
    this->pTurnController->Enable();

    this->pRobotDrive->CurvatureDrive(0.2, 0.2, true);

	return;
}

/* This function is invoked periodically by the PID Controller, */
/* based upon navX MXP yaw angle input and PID Coefficients.    */
void DriveTrain::PIDWrite(double output)
{
    this->dRotateToAngleRate = output;

    return;
}

