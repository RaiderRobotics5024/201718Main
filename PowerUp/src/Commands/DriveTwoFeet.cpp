#include "DriveTwoFeet.h"

/**
 *
 */

DriveTwoFeet::DriveTwoFeet()
{
	std::cout << "[DriveTwoFeet] Constructed" << std::endl;

	if (CommandBase::pDriveTrain != nullptr)	{
		Requires(CommandBase::pDriveTrain);
	} else {
		std::cout << "[DriveTwoFeet] driveTrain is null!" << std::endl;
	}
}

/**
 *
 */

void DriveTwoFeet::Initialize()
{
	std::cout << "[DriveTwoFeet] Initialized" << std::endl;

	WPI_TalonSRX* _talon = new can::WPI_TalonSRX(LEFT_FRONT_MOTOR_ID);
	//	WPI_TalonSRX* _talon = CommandBase::pDriveTrain->pLeftFrontMotor;

	/* lets grab the 360 degree position of the MagEncoder's absolute position */
	/* mask out the bottom12 bits, we don't care about the wrap arounds */
	int absolutePosition = _talon->GetSelectedSensorPosition(0) & 0xFFF;

	/* use the low level API to set the quad encoder signal */
	_talon->SetSelectedSensorPosition(absolutePosition, PID_LOOP_INDEX, TIMEOUT_MS);

	/* choose the sensor and sensor direction */
	_talon->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, PID_LOOP_INDEX, TIMEOUT_MS);
	_talon->SetSensorPhase(true);

	/* set the peak and nominal outputs, 12V means full */
	_talon->ConfigNominalOutputForward(0, TIMEOUT_MS);
	_talon->ConfigNominalOutputReverse(0, TIMEOUT_MS);
	_talon->ConfigPeakOutputForward(1, TIMEOUT_MS);
	_talon->ConfigPeakOutputReverse(-1, TIMEOUT_MS);

	/* set closed loop gains in slot0 */
	_talon->Config_kF(PID_LOOP_INDEX, 0.0, TIMEOUT_MS);
	_talon->Config_kP(PID_LOOP_INDEX, 0.1, TIMEOUT_MS);
	_talon->Config_kI(PID_LOOP_INDEX, 0.0, TIMEOUT_MS);
	_talon->Config_kD(PID_LOOP_INDEX, 0.0, TIMEOUT_MS);
}

/**
 *
 */

void DriveTwoFeet::Execute()
{
	/* get gamepad axis */
	double leftYstick = CommandBase::pOI->GetJoystick()->GetY(XboxController::kLeftHand);
	double motorOutput = _talon->GetMotorOutputPercent();
	bool button1 = CommandBase::pOI->GetJoystick()->GetAButton();
	bool button2 = CommandBase::pOI->GetJoystick()->GetBButton();

	/* prepare line to print */
	_sb.append("\tout:");
	_sb.append(std::to_string(motorOutput));
	_sb.append("\tpos:");
	_sb.append(std::to_string(_talon->GetSelectedSensorPosition(PID_LOOP_INDEX)));

	/* on button1 press enter closed-loop mode on target position */
	if (!_lastButton1 && button1)
	{
		/* Position mode - button just pressed */
		targetPositionRotations = leftYstick * 10.0 * 4096; /* 50 Rotations in either direction */
		_talon->Set(ControlMode::Position, targetPositionRotations); /* 50 rotations in either direction */
	}

	/* on button2 just straight drive */
	if (button2)
	{
		/* Percent voltage mode */
		_talon->Set(ControlMode::PercentOutput, leftYstick);
	}

	/* if Talon is in position closed-loop, print some more info */
	if (_talon->GetControlMode() == ControlMode::Position)
	{
		/* append more signals to print when in speed mode. */
		_sb.append("\terrNative:");
		_sb.append(std::to_string(_talon->GetClosedLoopError(PID_LOOP_INDEX)));
		_sb.append("\ttrg:");
		_sb.append(std::to_string(targetPositionRotations));
	}

	/* print every ten loops, printing too much too fast is generally bad for performance */
	if (++_loops >= 10)
	{
		_loops = 0;
		printf("%s\n", _sb.c_str());
	}
	_sb.clear();
	/* save button state for on press detect */
	_lastButton1 = button1;
}

/**
 *
 */

bool DriveTwoFeet::IsFinished()
{
	return false;
}

/**
 *
 */

void DriveTwoFeet::End()
{
	std::cout << "[DriveTwoFeet] Ending" << std::endl;

}

/**
 *
 */

void DriveTwoFeet::Interrupted()
{
	std::cout << "[DriveTwoFeet] Interrupted" << std::endl;
}
