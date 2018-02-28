#include "ExtendSFM.h"

ExtendSFM::ExtendSFM()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(CommandBase::pSFM);
}

// Called just before this Command runs the first time
void ExtendSFM::Initialize()
{
	SmartDashboard::PutNumber("SFM", 1);
	SetTimeout(2);
}

// Called repeatedly when this Command is scheduled to run
void ExtendSFM::Execute()
{
	CommandBase::pSFM->SetForward();
}

// Make this return true when this Command no longer needs to run execute()
bool ExtendSFM::IsFinished()
{
	if(IsTimedOut()){ //time out
		return true;
	}else{
		return false;
	}
}

// Called once after isFinished returns true
void ExtendSFM::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ExtendSFM::Interrupted()
{

}
