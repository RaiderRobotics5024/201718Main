#include "RumbleInRange.h"

RumbleInRange::RumbleInRange()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(CommandBase::pBIOS);
}

// Called just before this Command runs the first time
void RumbleInRange::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void RumbleInRange::Execute()
{
	CommandBase::pBIOS->RumbleWhenRange(Preferences::GetInstance()->GetDouble("Ultra_Rumble_Target", 61.0), Preferences::GetInstance()->GetDouble("Ultra_Rumble_Variance", 10.0));
}

// Make this return true when this Command no longer needs to run execute()
bool RumbleInRange::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void RumbleInRange::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RumbleInRange::Interrupted()
{
	End();
}
