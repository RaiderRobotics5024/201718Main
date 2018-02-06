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
	pLeftRearMotor->Follow(*pLeftFrontMotor);

	this->pRightFrontMotor = new can::WPI_TalonSRX(RIGHT_FRONT_MOTOR_ID);
	this->pRightRearMotor = new can::WPI_TalonSRX(RIGHT_REAR_MOTOR_ID);
	pRightRearMotor->Follow(*pRightFrontMotor);

	this->pRobotDrive = new frc::DifferentialDrive(*pLeftFrontMotor, *pRightFrontMotor);

	/* [3] Adjust inverts so all motor drive in the correction direction */
//	pLeftFrontMotor->SetInverted(false);
//	pLeftRearMotor->SetInverted(false);
//	pRightFrontMotor->SetInverted(false);
//	pRightRearMotor->SetInverted(false);

	/* [4] adjust sensor phase so sensor moves positive when Talon LEDs are green */
	pLeftFrontMotor->SetSensorPhase(true);
	pRightFrontMotor->SetSensorPhase(true);

	pRobotDrive->SetSafetyEnabled(false);
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

int DriveTrain::GetLeftEncoderValue()
{
	double data = 0.0; // should be motor position from the enoder
	double equation = 2.0 * 3.1415 * WHEEL_RADIUS;

	return data * equation;
}

/**
 *
 */

int DriveTrain::GetRightEncoderValue()
{
	double data = 0.0; // should be motor position from the enoder
	double equation = 2.0 * 3.1415 * WHEEL_RADIUS;

	return data * equation;
}

// Put methods for controlling this subsystem here.
// Call these from Commands.

void DriveTrain::Drive(XboxController* joystick)
{
	std::stringstream work;

	/* get joystick stick values */
	double forwardSpeed = joystick->GetY(XboxController::kLeftHand);  /* positive is forward */
	double turnAngle    = joystick->GetX(XboxController::kLeftHand);  /* positive is right */

	/* deadband joystick 10%*/
//	if (std::abs(forwardSpeed) < 0.10) forwardSpeed = 0;
//	if (std::abs(turnAngle   ) < 0.10) turnAngle = 0;

	pRobotDrive->ArcadeDrive(forwardSpeed, turnAngle);

	/* -------- [2] Make sure Joystick Forward is positive for FORWARD, and GZ is positive for RIGHT */
	work << " GF:" << forwardSpeed << " GT:" << turnAngle;

	/* get sensor values */
	//double leftPos = _leftFront->GetSelectedSensorPosition(0);
	//double rghtPos = _rghtFront->GetSelectedSensorPosition(0);
	double leftVelUnitsPer100ms = pLeftFrontMotor->GetSelectedSensorVelocity(0);
	double rghtVelUnitsPer100ms = pRightFrontMotor->GetSelectedSensorVelocity(0);

	work << " L:" << leftVelUnitsPer100ms << " R:" << rghtVelUnitsPer100ms;

	/* drive motor at least 25%, Talons will auto-detect if sensor is out of phase */
//	pLeftFrontMotor->GetFaults(_faults_L);
//	pRightFrontMotor->GetFaults(_faults_R);

//	if (_faults_L.SensorOutOfPhase) {
//		work << " L sensor is out of phase";
//	}
//	if (_faults_R.SensorOutOfPhase) {
//		work << " R sensor is out of phase";
//	}

	/* print to console */
	std::cout << work.str() << std::endl;
}
