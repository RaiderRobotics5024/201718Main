#include "Robot.h"
#include "ctre/Phoenix.h"
#include <Commands/Scheduler.h>
#include <iostream>
#include <string>

/**
 *
 */
Robot::~Robot()
{
	std::cout << "[Robot] Destroyed" << std::endl;

	delete this->pTalonSRX;
	delete this->pJoystick;

	return;
}

/**
 *
 */
void Robot::RobotInit()
{
	std::cout << "[Robot] RobotInit called" << std::endl;

	this->pTalonSRX = new TalonSRX(0);
	this->pJoystick = new Joystick(0);


	return;
}

/**
 *
 */

void Robot::DisabledInit()
{
	std::cout << "[Robot] DisabledInit called" << std::endl;

	return;
}

/**
 *
 */
void Robot::DisabledPeriodic()
{
	frc::Scheduler::GetInstance()->Run();

	return;
}

/**
 *
 */
void Robot::AutonomousInit()
{
	std::cout << "[Robot] Autonomous Initialized" << std::endl;

	return;
}

/**
 *
 */
void Robot::AutonomousPeriodic()
{
	return;
}

/**
 *
 */
void Robot::TeleopInit()
{
	std::cout << "[Robot] Teleop Initialized" << std::endl;

	/* lets grab the 360 degree position of the MagEncoder's absolute position */
	int absolutePosition = pTalonSRX->GetSelectedSensorPosition(0) & 0xFFF; /* mask out the bottom12 bits, we don't care about the wrap arounds */
	/* use the low level API to set the quad encoder signal */
	pTalonSRX->SetSelectedSensorPosition(absolutePosition, 0, 10);

	/* choose the sensor and sensor direction */
	pTalonSRX->ConfigSelectedFeedbackSensor( FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10);
	pTalonSRX->SetSensorPhase(true);

	/* set the peak and nominal outputs, 12V means full */
	pTalonSRX->ConfigNominalOutputForward(0, 10);
	pTalonSRX->ConfigNominalOutputReverse(0, 10);
	pTalonSRX->ConfigPeakOutputForward(1, 10);
	pTalonSRX->ConfigPeakOutputReverse(-1, 10);

	/* set closed loop gains in slot0 */
	pTalonSRX->Config_kF(0, 0.0, 10);
	pTalonSRX->Config_kP(0, 0.1, 10);
	pTalonSRX->Config_kI(0, 0.0, 10);
	pTalonSRX->Config_kD(0, 0.0, 10);

	return;
}

/**
 *
 */
void Robot::TeleopPeriodic()
{
	/* get gamepad axis */
	double leftYstick = pJoystick->GetY();
	double motorOutput = pTalonSRX->GetMotorOutputPercent();
	bool button1 = pJoystick->GetRawButton(1);
	bool button2 = pJoystick->GetRawButton(2);

	/* prepare line to print */
	_sb.append("\tout:");
	_sb.append(std::to_string(motorOutput));
	_sb.append("\tpos:");
	_sb.append(std::to_string(pTalonSRX->GetSelectedSensorPosition(0)));

	/* on button1 press enter closed-loop mode on target position */
	if (!_lastButton1 && button1)
	{
		/* Position mode - button just pressed */
		dTargetPositionRotations = leftYstick * 10.0 * 4096; /* 10 Rotations in either direction */
		pTalonSRX->Set(ControlMode::Position, dTargetPositionRotations); /* 10 rotations in either direction */

	}

	/* on button2 just straight drive */
	if (button2)
	{
		/* Percent voltage mode */
		pTalonSRX->Set(ControlMode::PercentOutput, leftYstick);
	}

	/* if Talon is in position closed-loop, print some more info */
	if (pTalonSRX->GetControlMode() == ControlMode::Position)
	{
		/* append more signals to print when in speed mode. */
		_sb.append("\terrNative:");
		_sb.append(std::to_string(pTalonSRX->GetClosedLoopError(0)));
		_sb.append("\ttrg:");
		_sb.append(std::to_string(dTargetPositionRotations));
	}

	/* print every ten loops, printing too much too fast is generally bad for performance */
	if (++_loops >= 10)
	{
		_loops = 0;
		std::cout << _sb.c_str() << std::endl;
//		printf("%s\n", _sb.c_str());
	}
	_sb.clear();
	/* save button state for on press detect */
	_lastButton1 = button1;

	return;
}

/**
 *
 */
void Robot::TestPeriodic()
{
	return;
}

/**
 *
 */
START_ROBOT_CLASS(Robot)
