#include "RotateWithGyro.h"

RotateWithGyro::RotateWithGyro()
{
	Requires(CommandBase::pDriveTrain);
	target = 0.0;

}

// Called just before this Command runs the first time
void RotateWithGyro::Initialize()
{
	target = (int)(CommandBase::pDriveTrain->GetGyro() + 180)%360;
	SetTimeout(5);
}

// Called repeatedly when this Command is scheduled to run
void RotateWithGyro::Execute()
{


}

// Make this return true when this Command no longer needs to run execute()
bool RotateWithGyro::IsFinished()
{
	if(IsTimedOut()){ //time out
		return true;
	}


	SmartDashboard::PutString("Current Task", "auto turn");

	double kP = 1.3;

	int angleDiff = ((int)(CommandBase::pDriveTrain->GetGyro()-target)) % 360 ; //angle diff
	double error = (1 - (( (double) abs( abs(angleDiff) - 180 ) / 180.0))) * kP;

	if(((angleDiff > 0 && angleDiff <= 180) || (angleDiff < -180))){
		CommandBase::pDriveTrain->TankDrive(((0.0 * error) + 1.0), -(0.0 * error + 1.0));
	}
	else if(((angleDiff < 0 && angleDiff >= -180) || (angleDiff > 180))){
		CommandBase::pDriveTrain->TankDrive(-(0.0 * error + 1.0), (0.0 * error + 1.0));
	}
	else{
		CommandBase::pDriveTrain->TankDrive(0.0f, 0.0f);
		return true;
	}

	return false;
}

// Called once after isFinished returns true
void RotateWithGyro::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RotateWithGyro::Interrupted()
{
	End();
}
