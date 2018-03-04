#include "Robot.h"
#include "Utilities/Log.h"
#include <string>
#include "Commands/Autonomous/RobotLeftSwitchLeft.h"
#include "Commands/Autonomous/RobotLeftSwitchRight.h"
#include "Commands/Autonomous/RobotCenterSwitchLeft.h"
#include "Commands/Autonomous/RobotCenterSwitchRight.h"
#include "Commands/Autonomous/RobotRightSwitchLeft.h"
#include "Commands/Autonomous/RobotRightSwitchRight.h"
#include "Commands/Autonomous/TestAutonomous.h"

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
	int _RP = 10; // 10 = Left, 20 = Center, 30 = Right
	int _SP =  1;  // 1 = Left, 2 = Right

	DriverStation& driverStation = frc::DriverStation::GetInstance();

	_RP = driverStation.GetLocation() * 10;

	std::string _GSM = driverStation.GetGameSpecificMessage();
	if (_GSM.length() > 0)
	{
		if (_GSM[0] == 'L')
		{
			_SP = 1; // switch is on the left
		}
		else if (_GSM[0] == 'R')
		{
			_SP = 2; // switch is on the right
		}
		else
		{
			_SP = 3; // use this for test mode
		}
		_SP = (_GSM[0] == 'L') ? 1 : 2;
	}
	else
	{
		_SP = 2; // go for right if GSM is empty
	}

	LOG("[Robot] Robot Position: " << _RP << " - Switch Position: " << _SP);

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
	case 13: pAutonomousCommand = new TestAutonomous        (); break;
	case 21: pAutonomousCommand = new RobotCenterSwitchLeft (); break;
	case 22: pAutonomousCommand = new RobotCenterSwitchRight(); break;
	case 23: pAutonomousCommand = new TestAutonomous        (); break;
	case 31: pAutonomousCommand = new RobotRightSwitchLeft  (); break;
	case 32: pAutonomousCommand = new RobotRightSwitchRight (); break;
	case 33: pAutonomousCommand = new TestAutonomous        (); break;
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
