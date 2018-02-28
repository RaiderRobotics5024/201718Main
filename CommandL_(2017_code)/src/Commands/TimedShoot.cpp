#include "TimedShoot.h"

TimedShoot::TimedShoot()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(CommandBase::pBIOS);
	displacement = -1; //default
}

TimedShoot::TimedShoot(double displacement)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(CommandBase::pBIOS);
	this->displacement = displacement;
}


// Called just before this Command runs the first time
void TimedShoot::Initialize()
{
	CommandBase::pBIOS->StartTimer();
	SetTimeout(5);
}

// Called repeatedly when this Command is scheduled to run
void TimedShoot::Execute()
{
	//default
	if(displacement == -1){
		CommandBase::pBIOS->Shoot(CommandBase::pBIOS->GetShootSpeed());
		if(CommandBase::pBIOS->GetCurrentTime() >= 1.0 ){ //kick
			CommandBase::pBIOS->Intake(CommandBase::pBIOS->GetIntakeSpeed());
		}
		//OI approved
	}else{
		CommandBase::pBIOS->Shoot(CommandBase::pBIOS->GetShootSpeed(displacement));
		if(CommandBase::pBIOS->GetCurrentTime() >= 1.0 ){ //kick
			CommandBase::pBIOS->Intake(CommandBase::pBIOS->GetIntakeSpeed());
		}
	}


}

// Make this return true when this Command no longer needs to run execute()
bool TimedShoot::IsFinished()
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
void TimedShoot::End()
{
	CommandBase::pBIOS->StopShoot();
	CommandBase::pBIOS->StopIntake();
	CommandBase::pBIOS->StopTimer();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TimedShoot::Interrupted()
{
	End();
}
