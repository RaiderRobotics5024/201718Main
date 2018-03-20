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

void DriveTrain::ReverseDrive(bool reverse){
	this->pRightFrontMotor->SetInverted(reverse);
	this->pRightRearMotor->SetInverted(reverse);
	this->pLeftFrontMotor->SetInverted(reverse);
	this->pLeftRearMotor->SetInverted(reverse);
	isReversed = reverse;
}

void DriveTrain::IsReversed(){
	return isReversed;
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
	pLeftFrontMotor->Config_kP(PID_LOOP_INDEX, TALON_PID_P, TIMEOUT_MS);
	pLeftFrontMotor->Config_kI(PID_LOOP_INDEX, TALON_PID_I, TIMEOUT_MS);
	pLeftFrontMotor->Config_kD(PID_LOOP_INDEX, TALON_PID_D, TIMEOUT_MS);
	pLeftFrontMotor->Config_kF(PID_LOOP_INDEX, TALON_PID_F, TIMEOUT_MS);

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
	this->dTargetPostionRotations = (distance / INCHES_PER_REVOLUTION) * TICKS_PER_REVOLUTION;
	pLeftFrontMotor->Set(ControlMode::Position, speed * dTargetPostionRotations);

	return;
}

/**
 * Used by Autonomous Commands
 */
void DriveTrain::Turn()
{
    this->pTurnController->Enable();

    double dSpeed = this->dRotateToAngleRate;

    if (this->pTurnController->GetSetpoint() < 0.0) dSpeed = dSpeed * -1;

    this->pRobotDrive->CurvatureDrive(dSpeed, 0.0, true);

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

/*
 *
 */

AHRS* DriveTrain::GetAHRS()
{
	return this->pGyro ;
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
double DriveTrain::GetTargetPosition()
{
	return this->dTargetPostionRotations;
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
	int absolutePosition = pLeftFrontMotor->GetSelectedSensorPosition(SLOT_INDEX) & 0xFFF; /* mask out the bottom12 bits, we don't care about the wrap arounds */
	/* use the low level API to set the quad encoder signal */
	pLeftFrontMotor->SetSelectedSensorPosition(absolutePosition, PID_LOOP_INDEX, TIMEOUT_MS);

	return;
}

/**
 *
 */
void DriveTrain::SetSetpoint(double setpoint)
{
	this->pTurnController->SetSetpoint(setpoint);

	return;
}

/**
 *
 */
void DriveTrain::Trace()
{
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
