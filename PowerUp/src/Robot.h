#ifndef _ROBOT_HG_
#define _ROBOT_HG_

#include <WPILib.h>
#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

#include "MotionProfile/CommandGroups/MPRobotCenterSwitchRightCG.h"

struct RobotPosition
{
	typedef enum
	{
		LEFT   = 10,
		CENTER = 20,
		RIGHT  = 30
	} RP;
};

struct SwitchPosition
{
	typedef enum
	{
		LEFT  = 1,
		RIGHT = 2,
		TEST  = 3
	} SP;
};

/**
 *
 */
class Robot : public frc::TimedRobot
{
public:
	// Robot Positions
	~Robot();
	void RobotInit() override;
	void DisabledInit() override;
	void DisabledPeriodic() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;
	void TestInit() override;
	void TestPeriodic() override;

	MPRobotCenterSwitchRightCG* pMotionProfileCommand;

private:

	int GetAutoType();

	frc::SendableChooser<int> scRobotPosition;
	frc::SendableChooser<int> scOverrideAuto;
	frc::Command* pAutonomousCommand;
};

#endif
