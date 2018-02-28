#include "ReverseDrive.h"

ReverseDrive::ReverseDrive()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(CommandBase::pDriveTrain);
}

// Called just before this Command runs the first time
void ReverseDrive::Initialize()
{
	//note: to reverse, JoystickDrive::Drive(Joystick* joy) is also used.
	if(CommandBase::pDriveTrain->IsReversed()){
		CommandBase::pDriveTrain->ReverseDrive(false);
	}else{
		CommandBase::pDriveTrain->ReverseDrive(true);
	}
}

// Called repeatedly when this Command is scheduled to run
void ReverseDrive::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool ReverseDrive::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void ReverseDrive::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ReverseDrive::Interrupted()
{
	End();
}
