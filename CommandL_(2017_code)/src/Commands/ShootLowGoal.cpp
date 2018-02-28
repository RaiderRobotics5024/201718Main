#include "ShootLowGoal.h"

ShootLowGoal::ShootLowGoal()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(CommandBase::pBIOS);
}

// Called just before this Command runs the first time
void ShootLowGoal::Initialize()
{
	SetTimeout(5);
}

// Called repeatedly when this Command is scheduled to run
void ShootLowGoal::Execute()
{
	CommandBase::pBIOS->StartTimer();
	CommandBase::pBIOS->LowGoal();
}

// Make this return true when this Command no longer needs to run execute()
bool ShootLowGoal::IsFinished()
{
	if(IsTimedOut()){ //time out
		return true;
	}

	if(CommandBase::pBIOS->GetCurrentTime() >= 2.0){
		return true;
	}else{
		return false;
	}
}

// Called once after isFinished returns true
void ShootLowGoal::End()
{
	CommandBase::pBIOS->StopIntake();
	CommandBase::pBIOS->StopTimer();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShootLowGoal::Interrupted()
{
	End();
}
