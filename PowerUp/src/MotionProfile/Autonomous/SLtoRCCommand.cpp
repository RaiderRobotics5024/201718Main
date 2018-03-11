#include "SLtoRCCommand.h"
#include "../../Utilities/Log.h"

/**
 *
 */
SLtoRCCommand::SLtoRCCommand()
{
	LOG("[SLtoRCCommand] Constructed");

	if ( CommandBase::pDriveTrain != nullptr )
	{
		Requires(CommandBase::pDriveTrain);
		this->pMotionProfiler = new SLtoRCProfile(*CommandBase::pDriveTrain->GetFrontLeftMotor());
	}
	else
	{
		LOG("[SLtoRCCommand] driveTrain is NULL");
	}

	return;
}

/**
 *
 */
SLtoRCCommand::~SLtoRCCommand()
{
	delete this->pMotionProfiler;

	return;
}

/**
 *
 */
void SLtoRCCommand::Initialize()
{
	LOG("[SLtoRCCommand] Initializing" );

	CommandBase::pDriveTrain->InitMotionProfiling();

	return;
}

/**
 *
 */
void SLtoRCCommand::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

	LOG("[SLtoRCCommand] Set Output: " << setOutput);

	CommandBase::pDriveTrain->GetFrontLeftMotor()->Set(ControlMode::MotionProfile, setOutput);

	this->pMotionProfiler->start();

	return;
}

/**
 *
 */
bool SLtoRCCommand::IsFinished()
{
	return false;
}

/**
 *
 */
void SLtoRCCommand::End()
{
	LOG("[SLtoRCCommand] Ending" );

	this->pMotionProfiler->reset();
	CommandBase::pDriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void SLtoRCCommand::Interrupted()
{
	LOG("[SLtoRCCommand] Interrupted" );

	CommandBase::pDriveTrain->ResetDrive();

	return;
}
