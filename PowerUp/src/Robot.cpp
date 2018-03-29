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

	if (this->pTalonSRX != nullptr)
	{
		this->pTalonSRX->Set(ControlMode::PercentOutput, 0);
		delete this->pTalonSRX;
		delete this->pFaults;
	}

	this->pTalonSRX = new WPI_TalonSRX(motor_id);
	this->pTalonSRX->SetInverted(false);
	this->pTalonSRX->SetSensorPhase(false);

	this->pTalonSRX->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 100);
// 	this->pTalonSRX->SetSelectedSensorPosition(0 & 0xFFF, 0, 100);

	/* set the peak and nominal outputs, 12V means full */
	this->pTalonSRX->ConfigNominalOutputForward(0, 100);
	this->pTalonSRX->ConfigNominalOutputReverse(0, 100);
	this->pTalonSRX->ConfigPeakOutputForward(1, 100);
	this->pTalonSRX->ConfigPeakOutputReverse(-1, 100);

	this->pTalonSRX->ConfigAllowableClosedloopError(0, 0, 100);

	/* set closed loop gains in slot0 */
	this->pTalonSRX->Config_kP(PID_LOOP_INDEX, 0.05, 100);
	this->pTalonSRX->Config_kI(PID_LOOP_INDEX, 0.00, 100);
	this->pTalonSRX->Config_kD(PID_LOOP_INDEX, 0.00, 100);
	this->pTalonSRX->Config_kF(PID_LOOP_INDEX, 0.00, 100);

// 	int absolutePosition = this->pTalonSRX->GetSelectedSensorPosition(0) & 0xFFF; /* mask out the bottom12 bits, we don't care about the wrap arounds */
	int abLeftPosition = this->pTalonSRX->GetSensorCollection().GetPulseWidthPosition();
	this->pTalonSRX->SetSelectedSensorPosition(abLeftPosition, 0, 100);
	
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

	// invert the motor with the X/B buttons
	if (this->pXboxController->GetXButtonPressed())
	{
		this->pTalonSRX->SetInverted(false);
	}
	else if (this->pXboxController->GetBButtonPressed())
	{
		this->pTalonSRX->SetInverted(true);
	}

	// run forward/backward with Y axis
	dMotorSpeed = this->pXboxController->GetY(XboxController::kLeftHand); // * -1; // positive motor speed to go forward
	
	if (this->pXboxController->GetYButton())
	{
		this->pTalonSRX->Set(ControlMode::PercentOutput, dMotorSpeed);
	}

	if (this->pXboxController->GetAButtonPressed()){
		IsPhase = !IsPhase;
		this->pTalonSRX->SetSensorPhase(IsPhase);
	}

	// start position closed loop 
	if (this->pXboxController->GetStartButtonPressed())
	{
		this->pTalonSRX->SetSelectedSensorPosition(0, 0, 100);
		double targetPositionRotations = 10.0 * 4096; /* 10 Rotations in either direction */
		this->pTalonSRX->Set(ControlMode::Position, targetPositionRotations); /* 10 rotations in either direction */
	}

	if (iCounter++ == 10)
	{
//		Robot::Trace();
		LOG("ID: " << iMotorId
			<< " QP: " << pTalonSRX->GetSensorCollection().GetQuadraturePosition()
			<< " QV: " << pTalonSRX->GetSensorCollection().GetQuadratureVelocity()
			<< " SP: " << pTalonSRX->GetSelectedSensorPosition(0)
			<< " SV: " << pTalonSRX->GetSelectedSensorVelocity(0)
			<< " IP: " << IsPhase
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
	if (iCounter++ < 20 ) return;
	
	iCounter = 0;
	
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
