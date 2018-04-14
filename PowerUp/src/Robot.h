#ifndef _ROBOT_HG_
#define _ROBOT_HG_

#include <WPILib.h>
#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <SmartDashboard/SendableChooser.h>
#include <NetworkTables/NetworkTable.h>
#include <NetworkTables/NetworkTableEntry.h>
#include <NetworkTables/NetworkTableInstance.h>
#include "Commands/ClimbScale.h"
#include "Commands/ControlElevator.h"
#include "Commands/ControlIntake.h"
#include "Commands/DriveWithJoystick.h"
#include "Commands/DriveWithTriggers.h"
#include "Commands/ToggleCompressor.h"

#include "MotionProfile/CommandGroups/MPTestAutonomousCG.h"

struct RobotPosition
{
	typedef enum
	{
		LEFT   = 10,
		CENTER = 20,
		RIGHT  = 30
	} Type;
};

struct RobotRole
{
	typedef enum
	{
		NONE         = 100,
		VAULT        = 200,
		OUR_SWITCH   = 300,
		THEIR_SWITCH = 400
	} Type;
};

struct SwitchPosition
{
	typedef enum
	{
		LEFT  = 1,
		RIGHT = 2,
		TEST  = 3
	} Type;
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

	// declare the commands
	ClimbScale*         pClimbScale;
	ControlElevator*	pControlElevator;
	ControlIntake*		pControlIntake;
	DriveWithJoystick*	pDriveWithJoystick;
	DriveWithTriggers*  pDriveWithTriggers;
	ToggleCompressor*   pToggleCompressor;

	MPTestAutonomousCG* pMotionProfileCommand;

private:
	int GetAutoType();

	frc::SendableChooser<int> scRobotPosition;
	frc::SendableChooser<int> scRobotRole;
	frc::SendableChooser<int> scOverrideAuto;
	frc::Command* pAutonomousCommand;

	nt::NetworkTableEntry xEntry;
	nt::NetworkTableEntry yEntry;

	double x = 0.0;
	double y = 0.0;
};

#endif
