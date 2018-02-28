#include <Commands/Intake.h>

Intake::Intake()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(CommandBase::pBIOS);
}

// Called just before this Command runs the first time
void Intake::Initialize()
{
	CommandBase::pBIOS->StartTimer();
	SetTimeout(5);
}

// Called repeatedly when this Command is scheduled to run
void Intake::Execute()
{
	CommandBase::pBIOS->Intake(CommandBase::pBIOS->GetIntakeSpeed());
}

// Make this return true when this Command no longer needs to run execute()
bool Intake::IsFinished()
{
	if(IsTimedOut()){ //time out
		return true;
	}
	if(CommandBase::pBIOS->IsSwitchSet()){
		return false;
	}else{
		return true;
	}

}

// Called once after isFinished returns true
void Intake::End()
{
	CommandBase::pBIOS->StopIntake();
	CommandBase::pBIOS->StopTimer();
	//CommandBase::pBIOS->InitializeCounter();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Intake::Interrupted()
{
	End();
}
