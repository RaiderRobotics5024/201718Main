#include "SRtoRCCommand.h"
#include "../../Utilities/Log.h"

/**
 *
 */
SRtoRCCommand::SRtoRCCommand()
{
	LOG("[SRtoRCCommand] Constructed");

	if ( CommandBase::pDriveTrain != nullptr )
	{
		Requires(CommandBase::pDriveTrain);
		this->pMotionProfiler = new SRtoRCProfile(*CommandBase::pDriveTrain->GetFrontLeftMotor());
	}
	else
	{
		LOG("[SRtoRCCommand] driveTrain is NULL");
	}

	return;
}

/**
 *
 */
SRtoRCCommand::~SRtoRCCommand()
{
	delete this->pMotionProfiler;

	return;
}

/**
 *
 */
void SRtoRCCommand::Initialize()
{
	LOG("[SRtoRCCommand] Initializing" );

	CommandBase::pDriveTrain->InitMotionProfiling();

	return;
}

/**
 *
 */
void SRtoRCCommand::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

	LOG("[SRtoRCCommand] Set Output: " << setOutput);

	CommandBase::pDriveTrain->GetFrontLeftMotor()->Set(ControlMode::MotionProfile, setOutput);

	this->pMotionProfiler->start();

	return;
}

/**
 *
 */
bool SRtoRCCommand::IsFinished()
{
	return false;
}

/**
 *
 */
void SRtoRCCommand::End()
{
	LOG("[SRtoRCCommand] Ending" );

	this->pMotionProfiler->reset();
	CommandBase::pDriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void SRtoRCCommand::Interrupted()
{
	LOG("[SRtoRCCommand] Interrupted" );

	CommandBase::pDriveTrain->ResetDrive();

	return;
}
