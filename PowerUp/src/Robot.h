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
#include "Commands/Gripper.h"

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
	void TestInit() override;
	void TestPeriodic() override;

	// declare the commands
	ClimbScale*        pClimbScale;
	ControlElevator*   pControlElevator;
	DriveWithJoystick* pDriveWithJoystick;
	Gripper*           pGripper;

private:
	int GetAutoType();

	frc::Command* pAutonomousCommand;
};

#endif
