#include "JoystickDrive.h"


JoystickDrive::JoystickDrive()
{
	Requires(CommandBase::pDriveTrain);
}

// Called just before this Command runs the first time
void JoystickDrive::Initialize()
{
	//CommandBase::pDriveTrain->ResetEncoders();
}

// Called repeatedly when this Command is scheduled to run
void JoystickDrive::Execute()
{
	CommandBase::pDriveTrain->Drive(CommandBase::pOI->GetDrive());
}


// Make this return true when this Command no longer needs to run execute()
bool JoystickDrive::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void JoystickDrive::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void JoystickDrive::Interrupted()
{
	End();
}
