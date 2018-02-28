#include "DriveForward.h"

void DriveForward::init(double dist, double maxSpeed) {
	Requires(CommandBase::pDriveTrain);
	distance = dist;
	driveSpeed = maxSpeed;
	error = 0;
}

DriveForward::DriveForward() {
	init(10, 0.5);
}

DriveForward::DriveForward(double dist) {
	init(dist, 0.5);
}

DriveForward::DriveForward(double dist, double maxSpeed) {
	init(dist, maxSpeed);
}

// Called just before this Command runs the first time
void DriveForward::Initialize() {
	CommandBase::pDriveTrain->pRightFrontMotor->SetPosition(0);
	CommandBase::pDriveTrain->pLeftFrontMotor->SetPosition(0);
	SetTimeout(10);
}

// Called repeatedly when this Command is scheduled to run
void DriveForward::Execute()
{
	if (distance > 0) {
		CommandBase::pDriveTrain->TankDrive(driveSpeed, driveSpeed);
	} else if (distance < 0) {
		CommandBase::pDriveTrain->TankDrive(-driveSpeed, -driveSpeed);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool DriveForward::IsFinished()
{
	if(IsTimedOut()){ //time out
		return true;
	}

	if (CommandBase::pDriveTrain->GetLeftEncoderValue() >= distance) {
		return true;
	} else {
		return false;
	}
}

// Called once after isFinished returns true
void DriveForward::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveForward::Interrupted()
{

}
