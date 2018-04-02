#include "Robot.h"
#include <iostream>

#define LOG(x) { std::cout << x << std::endl; }

/**
 *
 */
Robot::Robot()
{
	SmartDashboard::init();

	LOG("ROBOT Constructed");

	iMotorId = 1;
	iCounter = 0;
	dMotorSpeed = 0.0;
	IsInverted = false;
	IsPhase = false;
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
	LOG("Setting ID: " << motor_id);

	// delete previous motor if initialized
	if (this->pTalonSRX != nullptr)
	{
		this->pTalonSRX->Set(ControlMode::PercentOutput, 0);
		delete this->pTalonSRX;
		delete this->pFaults;
	}

	this->pTalonSRX = new WPI_TalonSRX(motor_id);
	this->pTalonSRX->SetInverted(false);
	this->IsInverted = false;

	this->pTalonSRX->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 100);
	this->pTalonSRX->SetSensorPhase(false);
	this->IsPhased = false;

	/* set the peak and nominal outputs, 12V means full */
	this->pTalonSRX->ConfigNominalOutputForward(0, 100);
	this->pTalonSRX->ConfigNominalOutputReverse(0, 100);
	this->pTalonSRX->ConfigPeakOutputForward(1, 100);
	this->pTalonSRX->ConfigPeakOutputReverse(-1, 100);

	this->pTalonSRX->ConfigAllowableClosedloopError(0, 0, 100);

	/* set closed loop gains in slot0 */
	this->pTalonSRX->Config_kP(0, 0.05, 100);
	this->pTalonSRX->Config_kI(0, 0.00, 100);
	this->pTalonSRX->Config_kD(0, 0.00, 100);
	this->pTalonSRX->Config_kF(0, 0.00, 100);

// 	int absolutePosition = this->pTalonSRX->GetSelectedSensorPosition(0) & 0xFFF; /* mask out the bottom12 bits, we don't care about the wrap arounds */
	int absolutePosition = this->pTalonSRX->GetSensorCollection().GetPulseWidthPosition();
	this->pTalonSRX->SetSelectedSensorPosition(absolutePosition, 0, 100);
	
	this->pFaults = new Faults();
	pTalonSRX->GetFaults(*pFaults);

	return;
}

/**
 *
 */
void Robot::TeleopPeriodic()
{
	// switch the motor with the left/right bumpers
	if (pXboxController->GetBumperPressed(XboxController::kLeftHand))
	{
		iMotorId--;
		if (iMotorId < 1) iMotorId = 1;
		SetMotor(iMotorId);
	}
	else if (pXboxController->GetBumperPressed(XboxController::kRightHand))
	{
		iMotorId++;
		if (iMotorId > 8) iMotorId = 8;
		SetMotor(iMotorId);
	}

	// invert the motor with the A button
	if (this->pXboxController->GetAButtonPressed())
	{
		this->IsInverted = !this->IsInverted;
		this->pTalonSRX->SetInverted(this->IsInverted);
	}

	// change the phase with the B Button
	if (this->pXboxController->GetBButtonPressed())
	{
		IsPhase = !IsPhase;
		this->pTalonSRX->SetSensorPhase(IsPhase);
	}

	// Y-axis goes from -1 (forward) to 1 (backward) but we want
	// the motor speed to be from 1 (forward) to -1 (reverse) so multiply by -1
	dMotorSpeed = this->pXboxController->GetY(XboxController::kLeftHand) * -1;
	
	// drive with joystick when Y button pressed
	if (this->pXboxController->GetYButton())
	{
		this->pTalonSRX->Set(ControlMode::PercentOutput, dMotorSpeed);
	}

	// enter position closed loop when start button pressed
	if (this->pXboxController->GetStartButtonPressed())
	{
		this->pTalonSRX->SetSelectedSensorPosition(0, 0, 100);
		double targetPositionRotations = 5.0 * 8192; /* 5 Rotations in either direction */
		this->pTalonSRX->Set(ControlMode::Position, targetPositionRotations);
	}

	if (iCounter++ == 10)
	{
//		Robot::Trace();
		LOG("ID: " << iMotorId
			<< " QP: " << this->pTalonSRX->GetSensorCollection().GetQuadraturePosition()
			<< " QV: " << this->pTalonSRX->GetSensorCollection().GetQuadratureVelocity()
			<< " SP: " << this->pTalonSRX->GetSelectedSensorPosition(0)
			<< " SV: " << this->pTalonSRX->GetSelectedSensorVelocity(0)
		    	<< " IN: " << (this->pTalonSRX->GetInverted() ? "True" : "False")
			<< " IP: " << (IsPhase ? "True" : "False")
		    	<< " MS: " << dMotorSpeed
		);
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
