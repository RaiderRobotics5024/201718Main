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

	this->pLeftFrontMotor->SetInverted(false);
	this->pLeftRearMotor->SetInverted(false);
	this->pLeftFrontMotor->SetNeutralMode(NeutralMode::Brake);
	this->pLeftRearMotor->SetNeutralMode(NeutralMode::Brake);

	this->pLeftFrontMotor->SetSensorPhase(true);
	this->pLeftRearMotor->SetSensorPhase(true);


	this->pRightFrontMotor = new can::WPI_TalonSRX(DRIVETRAIN_RIGHT_FRONT_MOTOR_ID);
	this->pRightRearMotor = new can::WPI_TalonSRX(DRIVETRAIN_RIGHT_REAR_MOTOR_ID);
	this->pRightRearMotor->Follow(*pRightFrontMotor);

	this->pRightFrontMotor->SetInverted(true);
	this->pRightRearMotor->SetInverted(true);
	this->pRightFrontMotor->SetNeutralMode(NeutralMode::Brake);
	this->pRightRearMotor->SetNeutralMode(NeutralMode::Brake);

	this->pRightFrontMotor->SetSensorPhase(true);
	this->pRightRearMotor->SetSensorPhase(true);

	this->pRobotDrive = new frc::DifferentialDrive(*pLeftFrontMotor, *pRightFrontMotor);

	pRobotDrive->SetSafetyEnabled(false);

	// Initialize the gyro
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

	int absolutePosition = pLeftFrontMotor->GetSelectedSensorPosition(SLOT_INDEX) & 0xFFF; /* mask out the bottom12 bits, we don't care about the wrap arounds */
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
void DriveTrain::InitMotionProfiling()
{
	pRightFrontMotor->Follow(*pLeftFrontMotor);

	pLeftFrontMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, TIMEOUT_MS);
	pLeftFrontMotor->SetSensorPhase(true);
	pLeftFrontMotor->ConfigNeutralDeadband(NEUTRAL_DEADBAND_PERCENT * 0.01,	TIMEOUT_MS);

	pLeftFrontMotor->Config_kF(0, 0.076, TIMEOUT_MS);
	pLeftFrontMotor->Config_kP(0, 2.000, TIMEOUT_MS);
	pLeftFrontMotor->Config_kI(0, 0.0  , TIMEOUT_MS);
	pLeftFrontMotor->Config_kD(0, 20.0 , TIMEOUT_MS);

	pLeftFrontMotor->ConfigMotionProfileTrajectoryPeriod(10, TIMEOUT_MS); //Our profile uses 10 ms timing
	/* status 10 provides the trajectory target for motion profile AND motion magic */
	pLeftFrontMotor->SetStatusFramePeriod(StatusFrameEnhanced::Status_10_MotionMagic, 10, TIMEOUT_MS);
}

/**
 * Used by Autonomous Commands
 */
void DriveTrain::Drive(double distance, double speed)
{
	double targetPositionRotations = (distance / INCHES_PER_REVOLUTION) * TICKS_PER_REVOLUTION;
	pLeftFrontMotor->Set(ControlMode::Position, speed * targetPositionRotations);

	return;
}

/**
 * Used by Autonomous Commands
 */
void DriveTrain::Turn(double setpoint)
{
    this->pTurnController->SetSetpoint(setpoint);
    this->pTurnController->Enable();

    this->pRobotDrive->CurvatureDrive(0.8, 0.8, true);

	return;
}

/**
 *
 */
void DriveTrain::ArcadeDrive(double xSpeed, double zRotation)
{
	this->pRobotDrive->ArcadeDrive(xSpeed, zRotation);

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
can::WPI_TalonSRX* DriveTrain::GetFrontLeftMotor()
{
	return this->pLeftFrontMotor;
}

/**
 *
 */
double DriveTrain::GetLeftPosition()
{
	return pLeftFrontMotor->GetSelectedSensorPosition(SLOT_INDEX);
}

/**
 *
 */
double DriveTrain::GetRightPosition()
{
	return pRightFrontMotor->GetSelectedSensorPosition(SLOT_INDEX);
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

	this->pRightRearMotor->Follow(*pRightRearMotor);
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

	pGyro->ZeroYaw();

	return;
}

/**
 *
 */
void DriveTrain::Trace()
{
	LOG("[Robot] Tracing");

	Trace(this->pLeftFrontMotor, "Left Front");
	Trace(this->pLeftRearMotor, "Left Rear");

	Trace(this->pRightFrontMotor, "Right Front");
	Trace(this->pRightRearMotor, "Right Rear");

	SmartDashboard::PutNumber("Gyro Angle", pGyro->GetAngle());
}

/**
 *
 */
void DriveTrain::Trace(WPI_TalonSRX* pTalonSRX, const std::string name)
{
	LOG("[Robot] Tracing: " << name);

	int baseId = pTalonSRX->GetBaseID();
	int version = pTalonSRX->GetFirmwareVersion();
	bool isInverted = pTalonSRX->GetInverted();

	double currentAmps = pTalonSRX->GetOutputCurrent();
	double outputV = pTalonSRX->GetMotorOutputVoltage();
	double busV = pTalonSRX->GetBusVoltage();
	double outputPerc = pTalonSRX->GetMotorOutputPercent();

	int quadPos = pTalonSRX->GetSensorCollection().GetQuadraturePosition();
	int quadVel = pTalonSRX->GetSensorCollection().GetQuadratureVelocity();

	int analogPos = pTalonSRX->GetSensorCollection().GetAnalogIn();
	int analogVel = pTalonSRX->GetSensorCollection().GetAnalogInVel();

	int selectedSensorPos = pTalonSRX->GetSelectedSensorPosition(SLOT_INDEX); /* sensor selected for PID Loop 0 */
	int selectedSensorVel = pTalonSRX->GetSelectedSensorVelocity(SLOT_INDEX); /* sensor selected for PID Loop 0 */
	int closedLoopErr = pTalonSRX->GetClosedLoopError(SLOT_INDEX); /* sensor selected for PID Loop 0 */
	double closedLoopAccum = pTalonSRX->GetIntegralAccumulator(SLOT_INDEX); /* sensor selected for PID Loop 0 */
	double derivErr = pTalonSRX->GetErrorDerivative(SLOT_INDEX);  /* sensor selected for PID Loop 0 */

	Faults faults;
	pTalonSRX->GetFaults(faults);

	SmartDashboard::PutNumber(name + " Base ID", baseId);
	SmartDashboard::PutNumber(name + " Version", version);
	SmartDashboard::PutBoolean(name + " Is Inverted", isInverted);

	SmartDashboard::PutNumber(name + " Current Amps", currentAmps);
	SmartDashboard::PutNumber(name + " Output Voltage", outputV);
	SmartDashboard::PutNumber(name + " Bus Voltage", busV);
	SmartDashboard::PutNumber(name + " Output Percent", outputPerc);

	SmartDashboard::PutNumber(name + " Quad Position", quadPos);
	SmartDashboard::PutNumber(name + " Quad Velocity", quadVel);

	SmartDashboard::PutNumber(name + " Analog In Position", analogPos);
	SmartDashboard::PutNumber(name + " Analog In Velocity", analogVel);

	SmartDashboard::PutNumber(name + " SS Position", selectedSensorPos);
	SmartDashboard::PutNumber(name + " SS Velocity", selectedSensorVel);
	SmartDashboard::PutNumber(name + " SS Closed Loop Error", closedLoopErr);
	SmartDashboard::PutNumber(name + " Integral Accumulator", closedLoopAccum);
	SmartDashboard::PutNumber(name + " Error Derivative", derivErr);

	SmartDashboard::PutBoolean(name + " Has Faults", faults.HasAnyFault());

	return;
}

/* This function is invoked periodically by the PID Controller, */
/* based upon navX MXP yaw angle input and PID Coefficients.    */
void DriveTrain::PIDWrite(double output)
{
    this->dRotateToAngleRate = output;

    return;
}
