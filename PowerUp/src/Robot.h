#ifndef _ROBOT_HG_
#define _ROBOT_HG_

#include <WPILib.h>
#include "ctre/Phoenix.h"
#include <string>

/**
 *
 */
class Robot : public frc::TimedRobot
{
public:
	~Robot();
	void RobotInit() override;
	void DisabledInit() override;
	void DisabledPeriodic() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;
	void TestPeriodic() override;

private:
	TalonSRX* pTalonSRX;
	Joystick* pJoystick;
	double dTargetPositionRotations;
	std::string _sb;
};

#endif
