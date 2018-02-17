#include "Commands/Autonomous/RobotCenterSwitchLeft.h"
#include "Commands/Autonomous/RobotCenterSwitchRight.h"
#include "Commands/Autonomous/RobotLeftSwitchLeft.h"
#include "Commands/Autonomous/RobotLeftSwitchRight.h"
#include "Commands/Autonomous/RobotRightSwitchLeft.h"
#include "Commands/Autonomous/RobotRightSwitchRight.h"
#include "Robot.h"
#include "Utilities/Log.h"


/**
 *
 */

Robot::~Robot()
{
	delete this->pDriveWithJoystick;
	delete this->pAutonomousCommand;

	return;
}

/**
 *
 */

void Robot::RobotInit()
{
	LOG("[Robot] Initialized");

	// instantiate the commands
	this->pDriveWithJoystick = new DriveWithJoystick();

	// Setup smartdashboard robot positions
	scRobotPosition.AddDefault("Left", 10);
	scRobotPosition.AddObject("Centre", 20);
	scRobotPosition.AddObject("Right", 30);
	frc::SmartDashboard::PutData("Robot Position", &scRobotPosition);

	// Setup smartdashboard switch positions
	scSwitchPosition.AddDefault("Left", 1);
	scSwitchPosition.AddObject("Right", 2);
	frc::SmartDashboard::PutData("Switch Position", &scSwitchPosition);

	return;
}

/**
 *
 */

void Robot::DisabledInit()
{
	return;
}

/**
 *
 */

void Robot::DisabledPeriodic()
{
	frc::Scheduler::GetInstance()->Run();

	return;
}

/**
 *
 */

void Robot::AutonomousInit()
{
	LOG("[Robot] Autonomous Initialized");

	int _RP = scRobotPosition.GetSelected();
	int _SP = scSwitchPosition.GetSelected();

	switch (_RP + _SP)
	{
	case 11: pAutonomousCommand = new RobotLeftSwitchLeft   (); break;
	case 12: pAutonomousCommand = new RobotLeftSwitchRight  (); break;
	case 21: pAutonomousCommand = new RobotCenterSwitchLeft (); break;
	case 22: pAutonomousCommand = new RobotCenterSwitchRight(); break;
	case 31: pAutonomousCommand = new RobotRightSwitchLeft  (); break;
	case 32: pAutonomousCommand = new RobotRightSwitchRight (); break;
	}

	if (pAutonomousCommand != nullptr)
	{
		LOG("Autonomous Command is null!");
		return;
	}

	LOG("[Robot] Starting autonomous");
	pAutonomousCommand->Start();

	return;
}

/**
 *
 */

void Robot::AutonomousPeriodic()
{
	frc::Scheduler::GetInstance()->Run();

	return;
}

/**
 *
 */

void Robot::TeleopInit()
{
	LOG("[Robot] Teleop Initialized");

	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// this line or comment it out.
	if (pAutonomousCommand != nullptr)
	{
		pAutonomousCommand->Cancel();
		pAutonomousCommand = nullptr;
	}

	if (pDriveWithJoystick != nullptr)
	{
		LOG("[Robot] Starting DriveWithJoystick");
		pDriveWithJoystick->Start();
	}
	else
	{
		LOG("[Robot] DriveWithJoystick is null!");
	}

	return;
}

/**
 *
 */

void Robot::TeleopPeriodic()
{
	LOG("[Robot] Running Scheduler");

	frc::Scheduler::GetInstance()->Run();

	return;
}

/**
 *
 */

void Robot::TestPeriodic()
{
	LOG("[Robot] TestPeriodic");

	return;
}

/**
 *
 */

START_ROBOT_CLASS(Robot)
