#include "DoTheThing.h"

DoTheThing::DoTheThing()
{
	Requires(CommandBase::pSFM);
	Requires(CommandBase::pBIOS);
}

// Called just before this Command runs the first time
void DoTheThing::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void DoTheThing::Execute()
{
	SmartDashboard::PutNumber("SFM", 6);
	if(CommandBase::pSFM->IsSwitchSet() == false) {
		SmartDashboard::PutNumber("SFM", 5);
		CommandBase::pSFM->SetForward();
		if (CommandBase::pBIOS->GetCurrentTime() >= 5) {
			CommandBase::pSFM->SetReverse();
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool DoTheThing::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void DoTheThing::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DoTheThing::Interrupted()
{

}
