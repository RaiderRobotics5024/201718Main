#include <Commands/CVControl.hpp>
#include <math.h>
#include <Utilities/Log.hpp>
#include <WPILib.h>
#include <ntcore.h>
#include <networktables/NetworkTableInstance.h>
#include "../RobotCFG.hpp"

CVControl::CVControl() {

	if (CommandBase::pDriveTrain != nullptr) {
		Requires(CommandBase::pDriveTrain);
	} else {
		LOG("[CVControl] Drivetrain is null!");
	}

	table = NetworkTable::GetTable("SmartDashboard");
	return;
}

// Called just before this Command runs the first time
void CVControl::Initialize() {


}

// Called repeatedly when this Command is scheduled to run
void CVControl::Execute() {

	double x = table->GetNumber("camx", 0.00);

	if(!this->Glock){
		this->lock = false;
		CommandBase::pDriveTrain->ArcadeDrive(0.0, x);
	} else{
		if(!this->lock){
	CommandBase::pDriveTrain->ArcadeDrive(0.0, 0.0);
	this->lock = true;
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool CVControl::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CVControl::End() {

}

void CVControl::Enable() {
	this->Glock = false;
}

void CVControl::Disable() {
	this->Glock = true;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CVControl::Interrupted() {

}
