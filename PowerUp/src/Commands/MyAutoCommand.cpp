/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "MyAutoCommand.h"

MyAutoCommand::MyAutoCommand()
{
	std::cout << "[MyAutoCommand] Constructed" << std::endl;

	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(&Robot::chassis);
	return;
}

// Called just before this Command runs the first time
void MyAutoCommand::Initialize()
{
	std::cout << "[MyAutoCommand] Initialized" << std::endl;

	return;
}

// Called repeatedly when this Command is scheduled to run
void MyAutoCommand::Execute()
{
	return;
}

// Make this return true when this Command no longer needs to run execute()
bool MyAutoCommand::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void MyAutoCommand::End()
{
	return;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MyAutoCommand::Interrupted()
{
	return;
}

