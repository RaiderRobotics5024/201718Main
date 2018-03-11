#include "RCtoSLCommand.h"
#include "../../Utilities/Log.h"

/**
 *
 */
RCtoSLCommand::RCtoSLCommand()
{
	LOG("[RCtoSLCommand] Constructed");

	if ( CommandBase::pDriveTrain != nullptr )
	{
		Requires(CommandBase::pDriveTrain);
		this->pMotionProfiler = new RCtoSLProfile(*CommandBase::pDriveTrain->GetFrontLeftMotor());
	}
	else
	{
		LOG("[RCtoSLCommand] driveTrain is NULL");
	}

	return;
}

/**
 *
 */
RCtoSLCommand::~RCtoSLCommand()
{
	delete this->pMotionProfiler;

	return;
}

/**
 *
 */
void RCtoSLCommand::Initialize()
{
	LOG("[RCtoSLCommand] Initializing" );

	CommandBase::pDriveTrain->InitMotionProfiling();

	return;
}

/**
 *
 */
void RCtoSLCommand::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

	LOG("[RCtoSLCommand] Set Output: " << setOutput);

	CommandBase::pDriveTrain->GetFrontLeftMotor()->Set(ControlMode::MotionProfile, setOutput);

	this->pMotionProfiler->start();

	return;
}

/**
 *
 */
bool RCtoSLCommand::IsFinished()
{
	return false;
}

/**
 *
 */
void RCtoSLCommand::End()
{
	LOG("[RCtoSLCommand] Ending" );

	this->pMotionProfiler->reset();
	CommandBase::pDriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void RCtoSLCommand::Interrupted()
{
	LOG("[RCtoSLCommand] Interrupted" );

	CommandBase::pDriveTrain->ResetDrive();

	return;
}
