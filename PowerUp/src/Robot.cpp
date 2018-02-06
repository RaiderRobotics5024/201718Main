#include "Robot.h"
#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

/**
 *
 */

Robot::~Robot()
{
	delete this->pDriveWithJoystick;
	delete this->pDefaultAutoCommand;
	delete this->pMyAutoCommand;
	delete this->pDriveTwoFeet;
}

/**
 *
 */

void Robot::RobotInit()
{
	std::cout << "[Robot] Initialized" << std::endl;

	// instantiate the commands
	this->pDriveWithJoystick = new DriveWithJoystick();
	this->pDefaultAutoCommand = new ExampleCommand();
	this->pMyAutoCommand = new MyAutoCommand();
	this->pDriveTwoFeet = new DriveTwoFeet();

	// Setup smartdashboard autonomous options
	m_chooser.AddDefault("Default Auto", pDefaultAutoCommand);
	m_chooser.AddObject("My Auto", pMyAutoCommand);
	frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
}

/**
 *
 */

void Robot::DisabledInit()
{
}

/**
 *
 */

void Robot::DisabledPeriodic()
{
	frc::Scheduler::GetInstance()->Run();
}

/**
 *
 */

void Robot::AutonomousInit()
{
	std::cout << "[Robot] Autonomous Initialized" << std::endl;

	std::string autoSelected = frc::SmartDashboard::GetString("Auto Selector", "Default");
	std::cout << "[Robot] Auto Selected: " << autoSelected << std::endl;

	pAutonomousCommand = m_chooser.GetSelected();

	if (pAutonomousCommand != nullptr) {
		std::cout << "[Robot] Starting autonomous" << std::endl;
		pAutonomousCommand->Start();
	} else {
		std::cout << "Autonomous Command is null!" << std::endl;
	}
}

/**
 *
 */

void Robot::AutonomousPeriodic()
{
	frc::Scheduler::GetInstance()->Run();
}

/**
 *
 */

void Robot::TeleopInit()
{
	std::cout << "[Robot] Teleop Initialized" << std::endl;

	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// this line or comment it out.
	if (pAutonomousCommand != nullptr) {
		pAutonomousCommand->Cancel();
		pAutonomousCommand = nullptr;
	}

	if (pDriveTwoFeet != nullptr) {
		std::cout << "[Robot] Starting pDriveTwoFeet" << std::endl;
		pDriveTwoFeet->Start();
	} else {
		std::cout << "[Robot] pDriveTwoFeet is nul!" << std::endl;
	}
}

/**
 *
 */

void Robot::TeleopPeriodic()
{
	std::cout << "[Robot] Running Scheduler" << std::endl;
	frc::Scheduler::GetInstance()->Run();
}

/**
 *
 */

void Robot::TestPeriodic()
{
	std::cout << "[Robot] TestPeriodic" << std::endl;
}

/**
 *
 */

START_ROBOT_CLASS(Robot)
