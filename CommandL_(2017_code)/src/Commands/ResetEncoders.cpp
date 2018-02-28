#include "ResetEncoders.h"

ResetEncoders::ResetEncoders()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(CommandBase::pDriveTrain);
}

// Called just before this Command runs the first time
void ResetEncoders::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void ResetEncoders::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool ResetEncoders::IsFinished()
{
	CommandBase::pDriveTrain->pLeftFrontMotor->SetPosition(0.0);
	CommandBase::pDriveTrain->pRightFrontMotor->SetPosition(0.0);

	return true;
}

// Called once after isFinished returns true
void ResetEncoders::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ResetEncoders::Interrupted()
{

}
