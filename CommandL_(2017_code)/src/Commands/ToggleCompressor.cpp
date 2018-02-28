#include "ToggleCompressor.h"

ToggleCompressor::ToggleCompressor(bool isStart)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(CommandBase::pSFM);
	this->isStart = isStart;
}

// Called just before this Command runs the first time
void ToggleCompressor::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void ToggleCompressor::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool ToggleCompressor::IsFinished()
{
	if(isStart){
		CommandBase::pSFM->StartCompressor();
		SmartDashboard::PutString("Compressor", "ON");
	}else{
		CommandBase::pSFM->StopCompressor();
		SmartDashboard::PutString("Compressor", "OFF");
	}
	return true;
}

// Called once after isFinished returns true
void ToggleCompressor::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ToggleCompressor::Interrupted()
{

}
