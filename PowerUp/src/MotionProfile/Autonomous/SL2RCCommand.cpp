#include "SL2RCCommand.h"
#include "../../Utilities/Log.h"

/**
 *
 */
SL2RCCommand::SL2RCCommand()
{
	LOG("[SL2RCCommand] Constructed");

	if ( CommandBase::pDriveTrain != nullptr )
	{
		Requires(CommandBase::pDriveTrain);
		this->pMotionProfiler = new SL2RCProfile(*CommandBase::pDriveTrain->GetFrontLeftMotor());
	}
	else
	{
		LOG("[SL2RCCommand] driveTrain is NULL");
	}

	return;
}

/**
 *
 */
void SL2RCCommand::Initialize()
{
	LOG("[SL2RCCommand] Initializing" );

	CommandBase::pDriveTrain->InitMotionProfiling();

	return;
}

/**
 *
 */
void SL2RCCommand::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

	LOG("[SL2RCCommand] Set Output: " << setOutput);

	CommandBase::pDriveTrain->GetFrontLeftMotor()->Set(ControlMode::MotionProfile, setOutput);

	this->pMotionProfiler->start();

	return;
}

/**
 *
 */
bool SL2RCCommand::IsFinished()
{
	return false;
}

/**
 *
 */
void SL2RCCommand::End()
{
	LOG("[SL2RCCommand] Ending" );

	this->pMotionProfiler->reset();
	CommandBase::pDriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void SL2RCCommand::Interrupted()
{
	LOG("[SL2RCCommand] Interrupted" );

	CommandBase::pDriveTrain->ResetDrive();

	return;
}
