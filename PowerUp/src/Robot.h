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
	void SetMotor(int);
	void TestPeriodic();
	void Trace();

private:
	int    iMotorId;
	int    iCounter;
	double dMotorSpeed;

	WPI_TalonSRX* pTalonSRX;
	Faults* pFaults;

	frc::XboxController* pXboxController;
};

#endif
