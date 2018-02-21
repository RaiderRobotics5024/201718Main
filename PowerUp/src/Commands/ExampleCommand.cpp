/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "ExampleCommand.h"

ExampleCommand::ExampleCommand()
{
	std::cout << "[ExampleCommand] Constructed" << std::endl;

	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(&Robot::chassis);

	return;
}

// Called just before this Command runs the first time
void ExampleCommand::Initialize()
{
	std::cout << "[ExampleCommand] Initialized" << std::endl;

	return;
}

// Called repeatedly when this Command is scheduled to run
void ExampleCommand::Execute()
{
	return;
}

// Make this return true when this Command no longer needs to run execute()
bool ExampleCommand::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void ExampleCommand::End()
{
	return;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ExampleCommand::Interrupted()
{
	return;
}

