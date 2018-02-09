#ifndef _ROBOT_HG_
#define _ROBOT_HG_

#include <iostream>
#include <memory>
#include <string>
#include <unistd.h>
#include <WPILib.h>
#include <IterativeRobot.h>
#include <ctre/Phoenix.h>
#include <XboxController.h>

/**
 *
 */

class Robot: public frc::IterativeRobot
{
public:
	TalonSRX *_srx;
	Joystick *_joy;
	std::stringstream _work;
	bool _btn1, _btn2, _btn3, _btn4;
	const bool kInvert = true; /* pick this based on your preference on what positive motor output should spin to */
	const bool kSensorPhase = false; /* pick this so self-test stops reporting sensor-out-of-phase */

	Robot();
	void DisabledInit();
	void DisabledPeriodic();
	void TeleopPeriodic();
	void CommonLoop();
};

#endif
