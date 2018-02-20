#include "DriveTrain.h"
#include <ctre/phoenix/MotorControl/NeutralMode.h>
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
	this->pLeftFrontMotor->SetNeutralMode(NeutralMode::Brake);
	this->pLeftRearMotor->SetNeutralMode(NeutralMode::Brake);

	this->pRightFrontMotor = new can::WPI_TalonSRX(RIGHT_FRONT_MOTOR_ID);
	this->pRightRearMotor = new can::WPI_TalonSRX(RIGHT_REAR_MOTOR_ID);
	this->pRightRearMotor->Follow(*pRightRearMotor);

	this->pRightFrontMotor->SetInverted(true);
	this->pRightRearMotor->SetInverted(true);
	this->pRightFrontMotor->SetNeutralMode(NeutralMode::Brake);
	this->pRightRearMotor->SetNeutralMode(NeutralMode::Brake);

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

void DriveTrain::Drive(double distance, double speed)
{
	double targetPositionRotations = (distance / INCHES_PER_REVOLUTION) * TICKS_PER_REVOLUTION;
	pLeftFrontMotor->Set(ControlMode::Position, speed * targetPositionRotations);

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

