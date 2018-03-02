#include "MotionProfileCommand.h"
#include "../../Utilities/Log.h"

/**
 *
 */
MotionProfileCommand::MotionProfileCommand()
{
	LOG("[MotionProfileCommand] Constructed");

	if ( CommandBase::pDriveTrain != nullptr )
	{
		Requires(CommandBase::pDriveTrain);
		this->pMotionProfiler = new MotionProfiler(*CommandBase::pDriveTrain->GetFrontLeftMotor());
	}
	else
	{
		LOG("[ClimbScale] driveTrain is NULL");
	}

	return;
}

/**
 *
 */
void MotionProfileCommand::Initialize()
{
	LOG("[MotionProfileCommand] Initializing" );

	CommandBase::pDriveTrain->InitMotionProfiling();

	return;
}

/**
 *
 */
void MotionProfileCommand::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

	LOG("[MotionProfileCommand] Set Output: " << setOutput);

	CommandBase::pDriveTrain->GetFrontLeftMotor()->Set(ControlMode::MotionProfile, setOutput);

	this->pMotionProfiler->start();

	return;
}

/**
 *
 */
bool MotionProfileCommand::IsFinished()
{
	return false;
}

/**
 *
 */
void MotionProfileCommand::End()
{
	LOG("[MotionProfileCommand] Ending" );

	this->pMotionProfiler->reset();
	CommandBase::pDriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void MotionProfileCommand::Interrupted()
{
	LOG("[MotionProfileCommand] Interrupted" );

	CommandBase::pDriveTrain->ResetDrive();

	return;
}
