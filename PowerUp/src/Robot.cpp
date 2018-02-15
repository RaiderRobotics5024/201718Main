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
	scRobotPosition.AddDefault("Left", 0);
	scRobotPosition.AddObject("Centre", 1);
	scRobotPosition.AddObject("Right", 2);
	frc::SmartDashboard::PutData("Robot Position", &scRobotPosition);

	// Setup smartdashboard switch positions
	scSwitchPosition.AddDefault("Left", 0);
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
	case 0: pAutonomousCommand = new RLSL();
		    break;
	}

	if (pAutonomousCommand != nullptr)
	{
		LOG("[Robot] Starting autonomous");
		pAutonomousCommand->Start();
	}
	else
	{
		LOG("Autonomous Command is null!");
	}

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
