#ifndef _ROBOT_HG_
#define _ROBOT_HG_

#include <WPILib.h>
#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include "Commands/ClimbScale.h"
#include "Commands/ControlElevator.h"
#include "Commands/DriveWithJoystick.h"
#include "Commands/ControlIntake.h"

#include "MotionProfile/Autonomous/CommandGroups/MPRobotCenterSwitchRightCG.h"

/**
 *
 */
class Robot : public frc::TimedRobot
{
public:
	// Robot Positions
	struct RobotPosition
	{
		typedef enum
		{
			LEFT   = 10,
			CENTER = 20,
			RIGHT  = 30
		} RP;
	};

	// Switch Positions
	struct SwitchPosition
	{
		typedef enum
		{
			LEFT  = 1,
			RIGHT = 2,
			TEST  = 3
		} SP;
	};

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

	// declare the commands
	ClimbScale*         pClimbScale;
	ControlElevator*	pControlElevator;
	DriveWithJoystick*	pDriveWithJoystick;
	ControlIntake*		pControlIntake;

	MPRobotCenterSwitchRightCG* pMotionProfileCommand;

private:

	int GetAutoType();

	frc::SendableChooser<int> scRobotPosition;
	frc::SendableChooser<int> scOverrideAuto;
	frc::Command* pAutonomousCommand;
};

#endif
