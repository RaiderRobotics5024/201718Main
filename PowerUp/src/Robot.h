#ifndef _ROBOT_HG_
#define _ROBOT_HG_

#include <WPILib.h>
#include <IterativeRobot.h>
#include <ctre/Phoenix.h>
#include <XboxController.h>

/**
 *
 */

class Robot : public frc::IterativeRobot
{
public:
	Robot();
	~Robot();
	void TeleopPeriodic();
	void SetMotor(int);
	void Trace();

private:
	int motor_id;
	double motor_speed;

	WPI_TalonSRX* pTalonSRX;
	frc::XboxController* pXboxController;
};

#endif
