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


	this->pRightFrontMotor = new can::WPI_TalonSRX(DRIVETRAIN_RIGHT_FRONT_MOTOR_ID);
	this->pRightRearMotor = new can::WPI_TalonSRX(DRIVETRAIN_RIGHT_REAR_MOTOR_ID);
	this->pRightRearMotor->Follow(*pRightFrontMotor);

	this->pRightFrontMotor->SetInverted(false);
	this->pRightRearMotor->SetInverted(false);
	this->pRightFrontMotor->SetNeutralMode(NeutralMode::Brake);
	this->pRightRearMotor->SetNeutralMode(NeutralMode::Brake);

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
	this->pRobotDrive->CurvatureDrive( xSpeed, zRotation, isQuickTurn );

	return;
}

/**
 *
 */
void DriveTrain::TankDrive( double leftSpeed, double rightSpeed )
{
	this->pRobotDrive->TankDrive( leftSpeed, rightSpeed );

	return;
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
	Trace(this->pLeftFrontMotor, "Left");
	Trace(this->pRightFrontMotor, "Right");

	SmartDashboard::PutNumber("Gyro Angle", pGyro->GetAngle());
}

/**
 *
 */
void DriveTrain::Trace(WPI_TalonSRX* pTalonSRX, const std::string name)
{
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

	SmartDashboard::PutNumber(name + std::string(" Base ID"), baseId);
	SmartDashboard::PutNumber(name + std::string(" Version"), version);
	SmartDashboard::PutBoolean(name + std::string(" Is Inverted"), isInverted);

	SmartDashboard::PutNumber(name + std::string(" Current Amps"), currentAmps);
	SmartDashboard::PutNumber(name + std::string(" Output Voltage"), outputV);
	SmartDashboard::PutNumber(name + std::string(" Bus Voltage"), busV);
	SmartDashboard::PutNumber(name + std::string(" Output Percent"), outputPerc);

	SmartDashboard::PutNumber(name + std::string(" Quad Position"), quadPos);
	SmartDashboard::PutNumber(name + std::string(" Quad Velocity"), quadVel);

	SmartDashboard::PutNumber(name + std::string(" Analog In Position"), analogPos);
	SmartDashboard::PutNumber(name + std::string(" Analog In Velocity"), analogVel);

	SmartDashboard::PutNumber(name + std::string(" SS Position"), selectedSensorPos);
	SmartDashboard::PutNumber(name + std::string(" SS Velocity"), selectedSensorVel);
	SmartDashboard::PutNumber(name + std::string(" SS Closed Loop Error"), closedLoopErr);
	SmartDashboard::PutNumber(name + std::string(" Integral Accumulator"), closedLoopAccum);
	SmartDashboard::PutNumber(name + std::string(" Error Derivative"), derivErr);

	SmartDashboard::PutBoolean(name + std::string(" Has Faults"), faults.HasAnyFault());

	return;
}

/* This function is invoked periodically by the PID Controller, */
/* based upon navX MXP yaw angle input and PID Coefficients.    */
void DriveTrain::PIDWrite(double output)
{
    this->dRotateToAngleRate = output;

    return;
}











