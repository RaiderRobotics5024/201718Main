#include "Robot.h"
#include <iostream>

/**
 *
 */

Robot::Robot()
{
	SmartDashboard::init();

	iMotorId = 0;
	iCounter = 0;
	dMotorSpeed = 0.0;
	SetMotor(iMotorId);

	this->pXboxController = new XboxController(0);

	return;
}

/**
 *
 */

Robot::~Robot()
{
	delete this->pXboxController;
	delete this->pTalonSRX;
	delete this->pFaults;

	return;
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
		delete this->pFaults;
	}

	this->pTalonSRX = new WPI_TalonSRX(motor_id);
	this->pTalonSRX->SetInverted(false);
	this->pTalonSRX->SetSensorPhase(true);
	this->pFaults = new Faults();
	pTalonSRX->GetFaults(*pFaults);

	return;
}

/**
 *
 */

void Robot::TestPeriodic()
{
	SmartDashboard::PutNumber("Motor ID", iMotorId);

	// switch the motor with the left/right bumpers
	if (pXboxController->GetBumperPressed(XboxController::kLeftHand))
	{
		iMotorId--;
		if (iMotorId < 0) iMotorId = 0;
		SetMotor(iMotorId);
	}
	else if (pXboxController->GetBumperPressed(XboxController::kRightHand))
	{
		iMotorId++;
		if (iMotorId > 8) iMotorId = 8;
		SetMotor(iMotorId);
	}

	// invert the motor with the X/B buttons
	if (this->pXboxController->GetXButton())
	{
		this->pTalonSRX->SetInverted(false);
	}
	else if (this->pXboxController->GetBButton())
	{
		this->pTalonSRX->SetInverted(true);
	}

	// run forward/backward with Y/A buttons
	if (this->pXboxController->GetYButton())
	{
		dMotorSpeed = 1.0;
	}
	else if (this->pXboxController->GetAButton())
	{
		dMotorSpeed = -1.0;
	}
	else
	{
		dMotorSpeed = 0.0;
	}

	pTalonSRX->Set(dMotorSpeed);

	if (iCounter++ == 10)
	{
		Robot::Trace();
		iCounter = 0;
	}

	return;
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


	SmartDashboard::PutNumber("Motor ID", iMotorId);
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

	SmartDashboard::PutBoolean("Has Faults", pFaults->HasAnyFault());

	return;
}

START_ROBOT_CLASS(Robot)
