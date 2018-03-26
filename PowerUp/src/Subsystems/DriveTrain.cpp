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

	// Initialize the left motors
	this->pLeftFrontMotor = new can::WPI_TalonSRX(DRIVETRAIN_LEFT_FRONT_MOTOR_ID);
	this->pLeftRearMotor = new can::WPI_TalonSRX(DRIVETRAIN_LEFT_REAR_MOTOR_ID);
	this->pLeftRearMotor->Follow(*pLeftFrontMotor);

	this->pLeftFrontMotor->SetInverted(true);
	this->pLeftRearMotor->SetInverted(true);
	this->pLeftFrontMotor->SetNeutralMode(NeutralMode::Brake);
	this->pLeftRearMotor->SetNeutralMode(NeutralMode::Brake);

	this->pLeftFrontMotor->SetSensorPhase(false);
	this->pLeftRearMotor->SetSensorPhase(false);

	// Initialize the right motors
	this->pRightFrontMotor = new can::WPI_TalonSRX(DRIVETRAIN_RIGHT_FRONT_MOTOR_ID);
	this->pRightRearMotor = new can::WPI_TalonSRX(DRIVETRAIN_RIGHT_REAR_MOTOR_ID);
	this->pRightRearMotor->Follow(*pRightFrontMotor);

	this->pRightFrontMotor->SetInverted(false);
	this->pRightRearMotor->SetInverted(false);
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
void DriveTrain::InitAutonomousMode()
{
	LOG("[DriveTrain] Autonomous Initialized");

	/* choose the sensor and sensor direction */
	this->pLeftFrontMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, PID_LOOP_INDEX, TIMEOUT_MS);
	this->pLeftFrontMotor->SetSensorPhase(false);

	/* set the peak and nominal outputs, 12V means full */
	this->pLeftFrontMotor->ConfigNominalOutputForward(0, TIMEOUT_MS);
	this->pLeftFrontMotor->ConfigNominalOutputReverse(0, TIMEOUT_MS);
	this->pLeftFrontMotor->ConfigPeakOutputForward(1, TIMEOUT_MS);
	this->pLeftFrontMotor->ConfigPeakOutputReverse(-1, TIMEOUT_MS);

	this->pLeftFrontMotor->ConfigAllowableClosedloopError(SLOT_INDEX, 0, TIMEOUT_MS);

	/* set closed loop gains in slot0 */
	this->pLeftFrontMotor->Config_kP(PID_LOOP_INDEX, 0.05, TIMEOUT_MS);
	this->pLeftFrontMotor->Config_kI(PID_LOOP_INDEX, 0.00, TIMEOUT_MS);
	this->pLeftFrontMotor->Config_kD(PID_LOOP_INDEX, 0.00, TIMEOUT_MS);
	this->pLeftFrontMotor->Config_kF(PID_LOOP_INDEX, 0.00, TIMEOUT_MS);

//	int abLeftPosition = this->pLeftFrontMotor->GetSelectedSensorPosition(SLOT_INDEX) & 0xFFF;
	int abLeftPosition = this->pLeftFrontMotor->GetSensorCollection().GetPulseWidthPosition();
	this->pLeftFrontMotor->SetSelectedSensorPosition(abLeftPosition, PID_LOOP_INDEX, TIMEOUT_MS);

	/* choose the sensor and sensor direction */
	this->pRightFrontMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, PID_LOOP_INDEX, TIMEOUT_MS);
	this->pRightFrontMotor->SetSensorPhase(false);

	/* set the peak and nominal outputs, 12V means full */
	this->pRightFrontMotor->ConfigNominalOutputForward(0, TIMEOUT_MS);
	this->pRightFrontMotor->ConfigNominalOutputReverse(0, TIMEOUT_MS);
	this->pRightFrontMotor->ConfigPeakOutputForward(1, TIMEOUT_MS);
	this->pRightFrontMotor->ConfigPeakOutputReverse(-1, TIMEOUT_MS);

	this->pRightFrontMotor->ConfigAllowableClosedloopError(SLOT_INDEX, 0, TIMEOUT_MS);

	/* set closed loop gains in slot0 */
	this->pRightFrontMotor->Config_kP(PID_LOOP_INDEX, 0.05, TIMEOUT_MS);
	this->pRightFrontMotor->Config_kI(PID_LOOP_INDEX, 0.00, TIMEOUT_MS);
	this->pRightFrontMotor->Config_kD(PID_LOOP_INDEX, 0.00, TIMEOUT_MS);
	this->pRightFrontMotor->Config_kF(PID_LOOP_INDEX, 0.00, TIMEOUT_MS);

//	int abRightPosition = this->pRightFrontMotor->GetSelectedSensorPosition(SLOT_INDEX) & 0xFFF;
	int abRightPosition = this->pRightFrontMotor->GetSensorCollection().GetPulseWidthPosition();
	this->pRightFrontMotor->SetSelectedSensorPosition(abRightPosition, PID_LOOP_INDEX, TIMEOUT_MS);

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
void DriveTrain::InitMotionProfiling()
{
	pLeftFrontMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, PID_LOOP_INDEX, TIMEOUT_MS);
	pLeftFrontMotor->SetSensorPhase(true);
	pLeftFrontMotor->ConfigNeutralDeadband(NEUTRAL_DEADBAND_PERCENT * 0.01, TIMEOUT_MS);

	pLeftFrontMotor->Config_kP(SLOT_INDEX, MP_PID_P, TIMEOUT_MS);
	pLeftFrontMotor->Config_kI(SLOT_INDEX, MP_PID_I, TIMEOUT_MS);
	pLeftFrontMotor->Config_kD(SLOT_INDEX, MP_PID_D, TIMEOUT_MS);
	pLeftFrontMotor->Config_kF(SLOT_INDEX, MP_PID_F, TIMEOUT_MS);

	pLeftFrontMotor->ConfigMotionProfileTrajectoryPeriod(5, TIMEOUT_MS); //Our profile uses 5 ms timing
	/* status 10 provides the trajectory target for motion profile AND motion magic */
	pLeftFrontMotor->SetStatusFramePeriod(StatusFrameEnhanced::Status_10_MotionMagic, 5, TIMEOUT_MS);

	pRightFrontMotor->SetInverted(true);

	pRightFrontMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, PID_LOOP_INDEX, TIMEOUT_MS);
	pRightFrontMotor->SetSensorPhase(true);
	pRightFrontMotor->ConfigNeutralDeadband(NEUTRAL_DEADBAND_PERCENT * 0.01, TIMEOUT_MS);

	pRightFrontMotor->Config_kP(SLOT_INDEX, MP_PID_P, TIMEOUT_MS);
	pRightFrontMotor->Config_kI(SLOT_INDEX, MP_PID_I, TIMEOUT_MS);
	pRightFrontMotor->Config_kD(SLOT_INDEX, MP_PID_D, TIMEOUT_MS);
	pRightFrontMotor->Config_kF(SLOT_INDEX, MP_PID_F, TIMEOUT_MS);

	pRightFrontMotor->ConfigMotionProfileTrajectoryPeriod(5, TIMEOUT_MS); //Our profile uses 5 ms timing
	/* status 10 provides the trajectory target for motion profile AND motion magic */
	pRightFrontMotor->SetStatusFramePeriod(StatusFrameEnhanced::Status_10_MotionMagic, 5, TIMEOUT_MS);
}

/**
 *
 */
void DriveTrain::DriveSetup()
{
	this->pLeftFrontMotor->Follow(*pRightFrontMotor);
	this->pRightFrontMotor->SetInverted(false);

	return;
}

/**
 * Used by Autonomous Commands
 */
void DriveTrain::Drive(double distance, double speed)
{
	double targetPositionRotations = (distance / INCHES_PER_REVOLUTION) * TICKS_PER_REVOLUTION;

	SetTargetPosition(targetPositionRotations * speed);

	this->pRightFrontMotor->Set(ControlMode::Position, GetTargetPosition());

	return;
}

/**
 *
 */
void DriveTrain::TurnSetup()
{
	this->pLeftFrontMotor->Follow(*pRightFrontMotor);
	this->pRightFrontMotor->SetInverted(true);

	return;
}

/**
 * Used by Autonomous Commands
 */
void DriveTrain::Turn()
{
    this->pTurnController->Enable();

    double dTurnRate = GetRotateToAngleRate();

    if (this->pTurnController->GetSetpoint() < 0.0) dTurnRate = dTurnRate * -1;

    this->pRobotDrive->ArcadeDrive(0.0, dTurnRate);

    return;
}

/**
 *
 */
void DriveTrain::ArcadeDrive(double xSpeed, double zRotation)
{
	this->pRobotDrive->ArcadeDrive(zRotation, xSpeed); // API parameter order is incorrect!

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
int DriveTrain::GetLeftClosedLoopError()
{
	return this->pLeftFrontMotor->GetClosedLoopError(SLOT_INDEX);
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
can::WPI_TalonSRX* DriveTrain::GetRightFrontMotor()
{
	return this->pRightFrontMotor;
}

/**
 *
 */
int DriveTrain::GetRightCosedLoopError()
{
	return this->pRightFrontMotor->GetClosedLoopError(SLOT_INDEX);
}

/**
 *
 */
double DriveTrain::GetRightDistance()
{
	return GetRightPosition() / TICKS_PER_REVOLUTION * INCHES_PER_REVOLUTION;
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
int DriveTrain::GetLeftVelocity()
{
	return pLeftFrontMotor->GetSelectedSensorVelocity(SLOT_INDEX);
}

/**
 *
 */
int DriveTrain::GetRightVelocity()
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
	this->pLeftFrontMotor->SetInverted(true);
	this->pLeftRearMotor->SetInverted(true);

	this->pRightRearMotor->Follow(*pRightFrontMotor);
	this->pRightFrontMotor->SetInverted(false);
	this->pRightRearMotor->SetInverted(false);

	return;
}

/**
 *
 */
void DriveTrain::ResetEncoders()
{
	LOG("[DriveTrain] Resetting encoders");

//	int abLeftPosition = this->pLeftFrontMotor->GetSelectedSensorPosition(SLOT_INDEX) & 0xFFF;
//	this->pLeftFrontMotor->SetSelectedSensorPosition(abLeftPosition, PID_LOOP_INDEX, 100);
//	this->pLeftFrontMotor->SetSelectedSensorPosition(0, PID_LOOP_INDEX, 100);

//	int abRightPosition = this->pRightFrontMotor->GetSelectedSensorPosition(SLOT_INDEX) & 0xFFF;
//	this->pRightFrontMotor->SetSelectedSensorPosition(abRightPosition, PID_LOOP_INDEX, 100);
//	this->pRightFrontMotor->SetSelectedSensorPosition(0, PID_LOOP_INDEX, 100);

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

	return;
}

/**
 *
 */
void DriveTrain::SetGyroPID(double p, double i, double d, double f)
{
	this->pTurnController->SetPID(p, i, d, f);

	return;
}

/**
 *
 */
void DriveTrain::SetTalonPID(double p, double i, double d, double f)
{
	this->pLeftFrontMotor->Config_kP(SLOT_INDEX, p, TIMEOUT_MS);
	this->pLeftFrontMotor->Config_kI(SLOT_INDEX, i, TIMEOUT_MS);
	this->pLeftFrontMotor->Config_kD(SLOT_INDEX, d, TIMEOUT_MS);
	this->pLeftFrontMotor->Config_kF(SLOT_INDEX, f, TIMEOUT_MS);

	this->pRightFrontMotor->Config_kP(SLOT_INDEX, p, TIMEOUT_MS);
	this->pRightFrontMotor->Config_kI(SLOT_INDEX, i, TIMEOUT_MS);
	this->pRightFrontMotor->Config_kD(SLOT_INDEX, d, TIMEOUT_MS);
	this->pRightFrontMotor->Config_kF(SLOT_INDEX, f, TIMEOUT_MS);

	return;
}

/**
 *
 */
void DriveTrain::SetMPPID(double p, double i, double d, double f)
{
	this->pLeftFrontMotor->Config_kP(SLOT_INDEX, p, TIMEOUT_MS);
	this->pLeftFrontMotor->Config_kI(SLOT_INDEX, i, TIMEOUT_MS);
	this->pLeftFrontMotor->Config_kD(SLOT_INDEX, d, TIMEOUT_MS);
	this->pLeftFrontMotor->Config_kF(SLOT_INDEX, f, TIMEOUT_MS);

	this->pRightFrontMotor->Config_kP(SLOT_INDEX, p, TIMEOUT_MS);
	this->pRightFrontMotor->Config_kI(SLOT_INDEX, i, TIMEOUT_MS);
	this->pRightFrontMotor->Config_kD(SLOT_INDEX, d, TIMEOUT_MS);
	this->pRightFrontMotor->Config_kF(SLOT_INDEX, f, TIMEOUT_MS);

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

/**
 *
 */
void DriveTrain::Trace()
{
	return;
}

/* This function is invoked periodically by the PID Controller, */
/* based upon navX MXP yaw angle input and PID Coefficients.    */
void DriveTrain::PIDWrite(double output)
{
    SetRotateToAngleRate(output);

    return;
}
