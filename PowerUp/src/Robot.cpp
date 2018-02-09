/**
 * [1] Enable robot and use gamepad y-axis to drive Talon.
 * [2] If sensor is out of phase, self-test will show the sticky fault.
 * [3] Use button 4 to read the CTRE pulse width and seed the quadrature/relative sensor.
 * [4] Use button 1,2,3 to set the sensor position to constant values.
 */
#include "Robot.h"

/**
 *
 */

Robot::Robot()
{
	this->_srx = new TalonSRX(0);
	this->_joy = new Joystick(0);
	std::stringstream _work;
	_btn1 = false, _btn2 = false, _btn3 = false, _btn4 = false;
}

/**
 * every time we enter disable, reinit
 */

void Robot::DisabledInit()
{
	/* choose quadrature/relative which has a faster update rate */
	_srx->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10);
	_srx->SetStatusFramePeriod(StatusFrame::Status_1_General_, 5, 10); /* Talon will send new frame every 5ms */
	_srx->SetSensorPhase(kSensorPhase);
	_srx->SetInverted(kInvert);
}

/**
 *
 */

void Robot::DisabledPeriodic()
{
	CommonLoop();
}

/**
 *
 */

void Robot::TeleopPeriodic()
{
	CommonLoop();
}

/**
 * every loop
 */

void Robot::CommonLoop()
{
	bool btn1 = _joy->GetRawButton(1); /* get buttons */
	bool btn2 = _joy->GetRawButton(2);
	bool btn3 = _joy->GetRawButton(3);
	bool btn4 = _joy->GetRawButton(4);

	/* on button unpress => press, change pos register */
	if (!_btn1 && btn1) {
		_srx->SetSelectedSensorPosition(-10, 0, 0);
		_work << "set:-10.0" << std::endl;
	}
	if (!_btn2 && btn2) {
		_srx->SetSelectedSensorPosition(-20, 0, 0);
		_work << "set:-20.0" << std::endl;
	}
	if (!_btn3 && btn3) {
		_srx->SetSelectedSensorPosition(+30, 0, 0);
		_work << "set:+30.0" << std::endl;
	}
	if (!_btn4 && btn4) {
		/* read the mag encoder sensor out */
		int read = (int) _srx->GetSensorCollection().GetPulseWidthPosition();
		/* flip pulse width to match selected sensor.  */
		if (kSensorPhase)
			read *= -1;
		if (kInvert)
			read *= -1;
		/* throw out the overflows, CTRE Encoder is 4096 units per rotation => 12 bitmask (0xFFF) */
		read = read & 0xFFF;
		/* set the value back with no overflows */
		_srx->SetSelectedSensorPosition(read, 0, 0);
		_work << "set:" << read << std::endl;
	}

	/* remove this and at most we get one stale print (one loop) */
	usleep(10e3);

	/* call get and serialize what we get */
	double read = _srx->GetSelectedSensorPosition(0);
	_work << "read:" << read << std::endl;

	/* print any rendered strings, and clear work */
	printf(_work.str().c_str());
	_work.str("");

	/* cache values for next loop comparisons */
	_btn1 = btn1;
	_btn2 = btn2;
	_btn3 = btn3;
	_btn4 = btn4;

	_srx->Set(ControlMode::PercentOutput, -1 * _joy->GetY());
}

START_ROBOT_CLASS(Robot)
