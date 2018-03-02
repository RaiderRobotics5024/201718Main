#include "Robot.h"
#include "Utilities/Log.h"
#include <string>
#include "Commands/Autonomous/RobotLeftSwitchLeft.h"
#include "Commands/Autonomous/RobotLeftSwitchRight.h"
#include "Commands/Autonomous/RobotCenterSwitchLeft.h"
#include "Commands/Autonomous/RobotCenterSwitchRight.h"
#include "Commands/Autonomous/RobotRightSwitchLeft.h"
#include "Commands/Autonomous/RobotRightSwitchRight.h"

/**
 *
 */
Robot::~Robot()
{
	delete this->pDriveWithJoystick;
	delete this->pGripper;
	delete this->pControlElevator;
	delete this->pAutonomousCommand;

	return;
}

/**
 *
 */
void Robot::RobotInit()
{
	LOG("[Robot] Initialized");

	// intialize the commands
	this->pClimbScale = new ClimbScale();
	this->pControlElevator = new ControlElevator();
	this->pDriveWithJoystick = new DriveWithJoystick();
	this->pGripper = new Gripper();

	// setup smartdashboard robot positions
	scRobotPosition.AddDefault("Left", 10);
	scRobotPosition.AddObject("Centre", 20);
	scRobotPosition.AddObject("Right", 30);
	frc::SmartDashboard::PutData("Robot Position", &scRobotPosition);

	// setup smartdashboard switch positions - used for test only
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

// Return sum of robot position and switch position
// Initially set the switch position from the smartdashboard
// but override that if we get game specific message
int Robot::GetAutoType()
{
	int _RP = scRobotPosition.GetSelected();
	int _SP = scSwitchPosition.GetSelected();
	std::string _GSM = frc::DriverStation::GetInstance().GetGameSpecificMessage();

	if (_GSM.length() > 0)
	{
		_SP = (_GSM[0] == 'L') ? 1 : 2;
	}

	LOG("[Robot] Robot Position: " << _RP << " - Switch Position: " << _SP << " - Game Data: " << _GSM);

	return _RP + _SP;
}

/**
 *
 */
void Robot::DisabledPeriodic()
{
	frc::Scheduler::GetInstance()->Run();

	return;
}

// set the autonomous command based on the value we get from GetAutoType
// default to Robot Center/Switch Right - the shortest path
void Robot::AutonomousInit()
{
	LOG("[Robot] Autonomous Initialized");

	int autoType = GetAutoType();

	LOG("[Robot] Auto Type: " << autoType);

	switch (autoType)
	{
	case 11: pAutonomousCommand = new RobotLeftSwitchLeft   (); break;
	case 12: pAutonomousCommand = new RobotLeftSwitchRight  (); break;
	case 21: pAutonomousCommand = new RobotCenterSwitchLeft (); break;
	case 22: pAutonomousCommand = new RobotCenterSwitchRight(); break;
	case 31: pAutonomousCommand = new RobotRightSwitchLeft  (); break;
	case 32: pAutonomousCommand = new RobotRightSwitchRight (); break;
	default: pAutonomousCommand = new RobotCenterSwitchRight(); break;
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

	// Stop the Autonomous Command
	if (pAutonomousCommand != nullptr)
	{
		pAutonomousCommand->Cancel();
		pAutonomousCommand = nullptr;
	}

	// Start the Teleop Commands
	if (pClimbScale != nullptr)
	{
		LOG("[Robot] Starting pClimbScale");
		pClimbScale->Start();
	}

	if (pControlElevator != nullptr)
	{
		LOG("[Robot] Starting pControlElevator");
		pControlElevator->Start();
	}

	if (pDriveWithJoystick != nullptr)
	{
		LOG("[Robot] Starting DriveWithJoystick");
		pDriveWithJoystick->Start();
	}

	if ( pGripper != nullptr )
	{
		LOG("[Robot] Starting Gripper");
		pGripper->Start();
	}

	return;
}

/**
 *
 */
void Robot::TeleopPeriodic()
{
	frc::Scheduler::GetInstance()->Run();

	return;
}

/**
 *
 */
void Robot::TestInit()
{
	this->pMotionProfileCommand = new MotionProfileCommand();
	this->pMotionProfileCommand->Start();

	return;
}

/**
 *
 */
void Robot::TestPeriodic()
{
	return;
}

// The main() function is hidden in this
//	pre-processor macro...
START_ROBOT_CLASS(Robot)
