#include "DriveTrain.h"
#include "../Utilities/Log.h"
#include "../RobotMap.h"
#include "../Commands/DriveWithJoystick.h"

/**
 *
 */
DriveTrain::DriveTrain() : frc::Subsystem("DriveTrain")
{
	LOG("[DriveTrain] Constructed");

	// Initialize the motors
	this->pLeftFrontMotor = new can::WPI_TalonSRX(DRIVETRAIN_LEFT_FRONT_MOTOR_ID);
	this->pLeftRearMotor = new can::WPI_TalonSRX(DRIVETRAIN_LEFT_REAR_MOTOR_ID);
	this->pLeftRearMotor->Follow(*pLeftFrontMotor);

	this->pLeftFrontMotor->SetInverted(IS_QBERT); // change this based on (false) production or (true) test robot
	this->pLeftRearMotor->SetInverted(IS_QBERT); // change this based on (false) production or (true) test robot
	this->pLeftFrontMotor->SetNeutralMode(NeutralMode::Brake);
	this->pLeftRearMotor->SetNeutralMode(NeutralMode::Brake);

	this->pLeftFrontMotor->SetSensorPhase(false);
	this->pLeftRearMotor->SetSensorPhase(false);

	this->pRightFrontMotor = new can::WPI_TalonSRX(DRIVETRAIN_RIGHT_FRONT_MOTOR_ID);
	this->pRightRearMotor = new can::WPI_TalonSRX(DRIVETRAIN_RIGHT_REAR_MOTOR_ID);
	this->pRightRearMotor->Follow(*pRightFrontMotor);

	this->pRightFrontMotor->SetInverted(!IS_QBERT); // change this based on (true) production or (false) test robot
	this->pRightRearMotor->SetInverted(!IS_QBERT); // change this based on (true) production or (false) test robot
	this->pRightFrontMotor->SetNeutralMode(NeutralMode::Brake);
	this->pRightRearMotor->SetNeutralMode(NeutralMode::Brake);

	this->pRightFrontMotor->SetSensorPhase(false);
	this->pRightRearMotor->SetSensorPhase(false);

	this->pRobotDrive = new frc::DifferentialDrive(*pLeftFrontMotor, *pRightFrontMotor);

	this->pLeftFrontMotor->SetSafetyEnabled(false);
	this->pLeftRearMotor->SetSafetyEnabled(false);
	this->pRightFrontMotor->SetSafetyEnabled(false);
	this->pRightRearMotor->SetSafetyEnabled(false);
	this->pRobotDrive->SetSafetyEnabled(false);

	DriveTrain::ResetEncoders();

	// Initialize the gyro
	// (See comment here about which port. We are using MXP, the one physically on top of the RoboRio
	//  https://www.pdocs.kauailabs.com/navx-mxp/software/roborio-libraries/c/)
	this->pGyro = new AHRS(SPI::Port::kMXP);
	this->pGyro->Reset();

	// Initialize the turn controller
	this->pTurnController = new PIDController(GYRO_PID_P, GYRO_PID_I, GYRO_PID_D, GYRO_PID_F, pGyro, this, 0.5);
	this->pTurnController->SetInputRange(-180.0f,  180.0f);
	this->pTurnController->SetOutputRange(-1.0, 1.0);
	this->pTurnController->SetAbsoluteTolerance(GYRO_TOLERANCE_DEGREES);
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
	delete this->pTurnController;

	return;
}

/**
 *
 */
void DriveTrain::InitAutonomousMode(bool inverted)
{
	LOG("[DriveTrain] Autonomous Initialized");

	SetEncoders();

	/* choose the sensor and sensor direction */
	pLeftFrontMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, PID_LOOP_INDEX, TIMEOUT_MS);
	pLeftFrontMotor->SetSensorPhase(false);

	/* set the peak and nominal outputs, 12V means full */
	pLeftFrontMotor->ConfigNominalOutputForward(0, TIMEOUT_MS);
	pLeftFrontMotor->ConfigNominalOutputReverse(0, TIMEOUT_MS);
	pLeftFrontMotor->ConfigPeakOutputForward(1, TIMEOUT_MS);
	pLeftFrontMotor->ConfigPeakOutputReverse(-1, TIMEOUT_MS);

	/* set closed loop gains in slot0 */
	pLeftFrontMotor->Config_kP(PID_LOOP_INDEX, 0.5, TIMEOUT_MS);
	pLeftFrontMotor->Config_kI(PID_LOOP_INDEX, 0.0, TIMEOUT_MS);
	pLeftFrontMotor->Config_kD(PID_LOOP_INDEX, 0.0, TIMEOUT_MS);
	pLeftFrontMotor->Config_kF(PID_LOOP_INDEX, 0.0, TIMEOUT_MS);

	pRightFrontMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, PID_LOOP_INDEX, TIMEOUT_MS);
	pRightFrontMotor->SetSensorPhase(true);
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
 * Used by Autonomous Commands
 */
void DriveTrain::Drive(double distance, double speed)
{
	double targetPositionRotations = (distance / INCHES_PER_REVOLUTION) * TICKS_PER_REVOLUTION;

	SetTargetPosition(targetPositionRotations * speed);

//	pLeftFrontMotor->Set(ControlMode::Position, GetTargetPosition() * -1);
	pRightFrontMotor->Set(ControlMode::Position, GetTargetPosition());

	return;
}

/**
 * Used by Autonomous Commands
 */
void DriveTrain::Turn()
{
    this->pTurnController->Enable();

    double dTurnRate = this->dRotateToAngleRate;

    if (this->pTurnController->GetSetpoint() < 0.0) dTurnRate = dTurnRate * -1;

    this->pRobotDrive->ArcadeDrive(0.0, dTurnRate);

    return;
}

/**
 *
 */
void DriveTrain::ArcadeDrive(double xSpeed, double zRotation)
{
	this->pRobotDrive->ArcadeDrive(zRotation, xSpeed); // API parameter order is incorrect

	return;
}

/**
 *
 */
void DriveTrain::CurvatureDrive(double xSpeed, double zRotation, bool isQuickTurn)
{
	this->pRobotDrive->CurvatureDrive(xSpeed, zRotation, isQuickTurn);

	return;
}

/**
 *
 */
void DriveTrain::TankDrive( double leftSpeed, double rightSpeed )
{
	this->pRobotDrive->TankDrive(leftSpeed, rightSpeed);

	return;
}

/**
 *
 */
AHRS* DriveTrain::GetAHRS()
{
	return this->pGyro;
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
can::WPI_TalonSRX* DriveTrain::GetLeftFrontMotor()
{
	return this->pLeftFrontMotor;
}

/**
 *
 */
can::WPI_TalonSRX* DriveTrain::GetRightFrontMotor()
{
	return this->pRightFrontMotor;
}

/**
 *
 */
double DriveTrain::GetLeftDistance()
{
	return GetLeftPosition() / TICKS_PER_REVOLUTION * INCHES_PER_REVOLUTION;
}

/**
 *
 */
double DriveTrain::GetLeftPosition()
{
	return this->pLeftFrontMotor->GetSelectedSensorPosition(SLOT_INDEX);
}

/**
 *
 */
double DriveTrain::GetRightPosition()
{
	return this->pRightFrontMotor->GetSelectedSensorPosition(SLOT_INDEX);
}

/**
 *
 */
double DriveTrain::GetRotateToAngleRate()
{
	return this->dRotateToAngleRate;
}

/**
 *
 */
double DriveTrain::GetTargetPosition()
{
	return this->dTargetPostionRotations;
}

/**
 *
 */
int DriveTrain::GetVelocity()
{
	return pRightFrontMotor->GetSelectedSensorVelocity(SLOT_INDEX);
}
/**
 *
 */
bool DriveTrain::IsDriving()
{
	return this->pGyro->IsMoving();
}

/**
 *
 */
bool DriveTrain::IsTurning()
{
	return this->pGyro->IsRotating();
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

	this->pRightRearMotor->Follow(*pRightFrontMotor);
	this->pRightFrontMotor->SetInverted(true);
	this->pRightRearMotor->SetInverted(true);

	return;
}

/**
 *
 */
void DriveTrain::ResetEncoders()
{
	LOG("[DriveTrain] Resetting encoders");

	this->pLeftFrontMotor->SetSelectedSensorPosition(0, PID_LOOP_INDEX, TIMEOUT_MS);
	this->pRightFrontMotor->SetSelectedSensorPosition(0, PID_LOOP_INDEX, TIMEOUT_MS);

	return;
}

/**
 *
 */
void DriveTrain::ResetGyro()
{
	LOG("[DriveTrain] Resetting the gyro");

	pGyro->Reset();
	pGyro->ZeroYaw();

	return;
}

/**
 *
 */
void DriveTrain::SetEncoders()
{
	int absLeftPosition = pLeftFrontMotor->GetSelectedSensorPosition(SLOT_INDEX) & 0xFFF; /* mask out the bottom12 bits, we don't care about the wrap arounds */
	int absRightPosition = pRightFrontMotor->GetSelectedSensorPosition(SLOT_INDEX) & 0xFFF; /* mask out the bottom12 bits, we don't care about the wrap arounds */
	/* use the low level API to set the quad encoder signal */
	pLeftFrontMotor->SetSelectedSensorPosition(absLeftPosition, PID_LOOP_INDEX, TIMEOUT_MS);
	pRightFrontMotor->SetSelectedSensorPosition(absRightPosition, PID_LOOP_INDEX, TIMEOUT_MS);

	return;
}

/**
 *
 */
void DriveTrain::SetRotateToAngleRate(double dRate)
{
	this->dRotateToAngleRate = dRate;
}

/**
 * Used by Autonomous Commands
 */
void DriveTrain::SetSetpoint(double dSetpoint)
{
    this->pTurnController->SetSetpoint(dSetpoint);

    return;
}

/**
 *
 */
void DriveTrain::SetTargetPosition(double dTargetPosition)
{
	this->dTargetPostionRotations = dTargetPosition;

	return;
}

/* This function is invoked periodically by the PID Controller, */
/* based upon navX MXP yaw angle input and PID Coefficients.    */
void DriveTrain::PIDWrite(double output)
{
    SetRotateToAngleRate(output);

    return;
}
