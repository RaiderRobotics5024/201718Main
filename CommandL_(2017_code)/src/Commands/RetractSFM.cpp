#include "RetractSFM.h"

RetractSFM::RetractSFM()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(CommandBase::pSFM);
}

// Called just before this Command runs the first time
void RetractSFM::Initialize()
{
	SetTimeout(2);
}

// Called repeatedly when this Command is scheduled to run
void RetractSFM::Execute()
{
	CommandBase::pSFM->SetReverse();
}

// Make this return true when this Command no longer needs to run execute()
bool RetractSFM::IsFinished()
{
	if(IsTimedOut()){ //time out
		return true;
	}
	else{
		return false;
	}
}

// Called once after isFinished returns true
void RetractSFM::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RetractSFM::Interrupted()
{
	End();
}
