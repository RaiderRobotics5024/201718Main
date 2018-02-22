#include "Robot.h"
#include "Utilities/Log.h"


Robot::~Robot()
{
	delete this->pDriveWithJoystick;
	delete this->pDefaultAutoCommand;
	delete this->pMyAutoCommand;
	delete this->pGripper;
	delete this->pControlElevator;

	return;
}


void Robot::RobotInit()
{
	LOG("[Robot] Initialized");

	// instantiate the commands
	this->pDriveWithJoystick = new DriveWithJoystick();
	this->pDefaultAutoCommand = new ExampleCommand();
	this->pMyAutoCommand = new MyAutoCommand();
	this->pGripper = new Gripper();
	this->pControlElevator = new ControlElevator();

	// Setup smartdashboard autonomous options
	m_chooser.AddDefault("Default Auto", pDefaultAutoCommand);
	m_chooser.AddObject("My Auto", pMyAutoCommand);
	frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

	return;
}


void Robot::DisabledInit()
{
	return;
}


void Robot::DisabledPeriodic()
{
	frc::Scheduler::GetInstance()->Run();

	return;
}


void Robot::AutonomousInit()
{
	LOG("[Robot] Autonomous Initialized");

	std::string autoSelected = frc::SmartDashboard::GetString("Auto Selector", "Default");
	LOG("[Robot] Auto Selected: " << autoSelected);

	pAutonomousCommand = m_chooser.GetSelected();

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


void Robot::AutonomousPeriodic()
{
	frc::Scheduler::GetInstance()->Run();

	return;
}


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
		//pDriveWithJoystick->Start();
	}
	else
	{
		LOG("[Robot] DriveWithJoystick is null!");
	}

	if ( pGripper != nullptr )
	{
		LOG("[Robot] Starting Gripper");
	}
	else
	{
		LOG("[Robot] Gripper is null!");
	}

	return;
}


void Robot::TeleopPeriodic()
{
	frc::Scheduler::GetInstance()->Run();

	return;
}


void Robot::TestPeriodic()
{
	return;
}

// The main() function is hidden in this
//	pre-processor macro...
START_ROBOT_CLASS(Robot)

