#include "Robot.h"

/**
 *
 */

const int DRIVE_JOYSTICK_PORT_ID = 0;

Robot::Robot()
{
	SmartDashboard::init();

	motor_id = 1;
	motor_speed = 0.0;
	SetMotor(motor_id);

	this->pXboxController = new XboxController(DRIVE_JOYSTICK_PORT_ID);
}

/**
 *
 */

Robot::~Robot()
{
	delete this->pXboxController;
	delete this->pTalonSRX;
}

/**
 *
 */

void Robot::SetMotor(int motor_id)
{
	if (this->pTalonSRX != nullptr)
	{
		this->pTalonSRX->Set(ControlMode::PercentOutput, 0);
		delete this->pTalonSRX;
	}

	this->pTalonSRX = new WPI_TalonSRX(motor_id);
	this->pTalonSRX->SetInverted(false);
	this->pTalonSRX->SetSensorPhase(true);
}

/**
 *
 */

void Robot::TeleopPeriodic()
{
	SmartDashboard::PutNumber("Motor ID", motor_id);

	if (pXboxController->GetBumperPressed(XboxController::kLeftHand)) {
		motor_id = (motor_id > 1) ? motor_id-- : 1;
		SetMotor(motor_id);
	} else if (pXboxController->GetBumperPressed(XboxController::kRightHand)) {
		motor_id = (motor_id < 8) ? motor_id++ : 8;
		SetMotor(motor_id);
	}

	if (this->pXboxController->GetXButton()) {
		this->pTalonSRX->SetInverted(false);
	} else if (this->pXboxController->GetBButton()) {
		this->pTalonSRX->SetInverted(true);
	}

	if (this->pXboxController->GetYButton()) {
		motor_speed = 1.0;
	} else if (this->pXboxController->GetAButton()) {
		motor_speed = -1.0;
	} else {
		motor_speed = 0.0;
	}

	pTalonSRX->Set(motor_speed);
}

/**
 *
 */

void Robot::Trace()
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

	int selectedSensorPos = pTalonSRX->GetSelectedSensorPosition(0); /* sensor selected for PID Loop 0 */
	int selectedSensorVel = pTalonSRX->GetSelectedSensorVelocity(0); /* sensor selected for PID Loop 0 */
	int closedLoopErr = pTalonSRX->GetClosedLoopError(0); /* sensor selected for PID Loop 0 */
	double closedLoopAccum = pTalonSRX->GetIntegralAccumulator(0); /* sensor selected for PID Loop 0 */
	double derivErr = pTalonSRX->GetErrorDerivative(0);  /* sensor selected for PID Loop 0 */

	SmartDashboard::PutNumber("Base ID", baseId);
	SmartDashboard::PutNumber("Version", version);
	SmartDashboard::PutBoolean("Is Inverted", isInverted);

	SmartDashboard::PutNumber("Current Amps", currentAmps);
	SmartDashboard::PutNumber("Output Voltage", outputV);
	SmartDashboard::PutNumber("Bus Voltage", busV);
	SmartDashboard::PutNumber("Output Percent", outputPerc);

	SmartDashboard::PutNumber("Quad Position", quadPos);
	SmartDashboard::PutNumber("Quad Velocity", quadVel);

	SmartDashboard::PutNumber("Analog In Position", analogPos);
	SmartDashboard::PutNumber("Analog In Velocity", analogVel);

	SmartDashboard::PutNumber("SS Position", selectedSensorPos);
	SmartDashboard::PutNumber("SS Velocity", selectedSensorVel);
	SmartDashboard::PutNumber("SS Closed Loop Error", closedLoopErr);
	SmartDashboard::PutNumber("Integral Accumulator", closedLoopAccum);
	SmartDashboard::PutNumber("Error Derivative", derivErr);
}

START_ROBOT_CLASS(Robot)
