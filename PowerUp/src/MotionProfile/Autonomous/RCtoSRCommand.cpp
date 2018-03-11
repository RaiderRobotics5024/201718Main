#include "RCtoSRCommand.h"
#include "../../Utilities/Log.h"

/**
 *
 */
RCtoSRCommand::RCtoSRCommand()
{
	LOG("[RCtoSRCommand] Constructed");

	if ( CommandBase::pDriveTrain != nullptr )
	{
		Requires(CommandBase::pDriveTrain);
		this->pMotionProfiler = new RCtoSRProfile(*CommandBase::pDriveTrain->GetFrontLeftMotor());
	}
	else
	{
		LOG("[RCtoSRCommand] driveTrain is NULL");
	}

	return;
}

/**
 *
 */
RCtoSRCommand::~RCtoSRCommand()
{
	delete this->pMotionProfiler;

	return;
}

/**
 *
 */
void RCtoSRCommand::Initialize()
{
	LOG("[RCtoSRCommand] Initializing" );

	CommandBase::pDriveTrain->InitMotionProfiling();

	return;
}

/**
 *
 */
void RCtoSRCommand::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

	LOG("[RCtoSRCommand] Set Output: " << setOutput);

	CommandBase::pDriveTrain->GetFrontLeftMotor()->Set(ControlMode::MotionProfile, setOutput);

	this->pMotionProfiler->start();

	return;
}

/**
 *
 */
bool RCtoSRCommand::IsFinished()
{
	return false;
}

/**
 *
 */
void RCtoSRCommand::End()
{
	LOG("[RCtoSRCommand] Ending" );

	this->pMotionProfiler->reset();
	CommandBase::pDriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void RCtoSRCommand::Interrupted()
{
	LOG("[RCtoSRCommand] Interrupted" );

	CommandBase::pDriveTrain->ResetDrive();

	return;
}
