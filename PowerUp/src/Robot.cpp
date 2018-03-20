#include "Robot.h"
#include "Utilities/Log.h"
#include "RobotMap.h"
#include <string>
#include "Commands/Autonomous/CommandGroups/JustDriveForward.h"
#include "Commands/Autonomous/CommandGroups/RobotLeftSwitchLeft.h"
#include "Commands/Autonomous/CommandGroups/RobotLeftSwitchRight.h"
#include "Commands/Autonomous/CommandGroups/RobotCenterSwitchLeft.h"
#include "Commands/Autonomous/CommandGroups/RobotCenterSwitchRight.h"
#include "Commands/Autonomous/CommandGroups/RobotRightSwitchLeft.h"
#include "Commands/Autonomous/CommandGroups/RobotRightSwitchRight.h"
#include "Commands/Autonomous/CommandGroups/TestAutonomous.h"

/**
 * This branch is used for PID tuning of the drivetrain motors and gyro rotation
 * PID values can be set on the smartdashboard then tested using the drive joystick
 * The only change here is sending the intial PID values to the smartdashboard,
 * all the real work is done in DriveWithJoystick.cpp
 */
Robot::~Robot()
{
	delete this->pDriveWithJoystick;

	if (this->pAutonomousCommand    != nullptr) delete this->pAutonomousCommand;
	if (this->pMotionProfileCommand != nullptr) delete this->pMotionProfileCommand;

	return;
}

/**
 *
 */
void Robot::RobotInit()
{
	LOG("[Robot] Initialized");

	SmartDashboard::PutBoolean("Is Drive Test:", false);
	SmartDashboard::PutBoolean("Is Turn  Test:", false);

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
	int _OA = scOverrideAuto.GetSelected();
	int _RP = scRobotPosition.GetSelected();
	int _SP = 0;
	std::string _GSM = frc::DriverStation::GetInstance().GetGameSpecificMessage();

	if (_GSM.length() > 0)
	{
		if (_GSM[0] == 'L')
		{
			_SP = SwitchPosition::LEFT; // switch is on the left
		}
		else if (_GSM[0] == 'R')
		{
			_SP = SwitchPosition::RIGHT; // switch is on the right
		}
		else if (_GSM[0] == 'T')
		{
			_SP = SwitchPosition::TEST; // used for testing autonomous scenarios without affecting real autonmous
		}
	}

	// do the override if robot left/switch right or robot right/switch left
	if ((_RP == RobotPosition::LEFT  && _SP == SwitchPosition::RIGHT && _OA > 0) ||
	    (_RP == RobotPosition::RIGHT && _SP == SwitchPosition::LEFT  && _OA > 0))
	{
		LOG("[Robot] Override Autonomous: " << _OA);

		return _OA;
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
	case 10: pAutonomousCommand = new JustDriveForward      (); break; // we didn't get the switch position from the FMS
	case 11: pAutonomousCommand = new RobotLeftSwitchLeft   (); break;
	case 12: pAutonomousCommand = new RobotLeftSwitchRight  (); break;
	case 13: pAutonomousCommand = new TestAutonomous        (); break;
	case 20: pAutonomousCommand = new JustDriveForward      (); break; // we didn't get the switch position from the FMS
	case 21: pAutonomousCommand = new RobotCenterSwitchLeft (); break;
	case 22: pAutonomousCommand = new RobotCenterSwitchRight(); break;
	case 23: pAutonomousCommand = new TestAutonomous        (); break;
	case 30: pAutonomousCommand = new JustDriveForward      (); break; // we didn't get the switch position from the FMS
	case 31: pAutonomousCommand = new RobotRightSwitchLeft  (); break;
	case 32: pAutonomousCommand = new RobotRightSwitchRight (); break;
	case 33: pAutonomousCommand = new TestAutonomous        (); break;
	case 98:
	case 99:
	default: pAutonomousCommand = new JustDriveForward      (); break;
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
	this->pDriveWithJoystick = new DriveWithJoystick();
	pDriveWithJoystick->Start();

	return;
}

/**
 *
 */
void Robot::TestPeriodic()
{
	frc::Scheduler::GetInstance()->Run();

	return;
}

// The main() function is hidden in this
//	pre-processor macro...
START_ROBOT_CLASS(Robot)
