#include "PY12RCCommand.h"
#include "../../Utilities/Log.h"

/**
 *
 */
PY12RCCommand::PY12RCCommand()
{
	LOG("[PY12RCCommand] Constructed");

	if ( CommandBase::pDriveTrain != nullptr )
	{
		Requires(CommandBase::pDriveTrain);
		this->pMotionProfiler = new PY12RCProfile(*CommandBase::pDriveTrain->GetFrontLeftMotor());
	}
	else
	{
		LOG("[PY12RCCommand] driveTrain is NULL");
	}

	return;
}

/**
 *
 */
void PY12RCCommand::Initialize()
{
	LOG("[PY12RCCommand] Initializing" );

	CommandBase::pDriveTrain->InitMotionProfiling();

	return;
}

/**
 *
 */
void PY12RCCommand::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

	LOG("[PY12RCCommand] Set Output: " << setOutput);

	CommandBase::pDriveTrain->GetFrontLeftMotor()->Set(ControlMode::MotionProfile, setOutput);

	this->pMotionProfiler->start();

	return;
}

/**
 *
 */
bool PY12RCCommand::IsFinished()
{
	return false;
}

/**
 *
 */
void PY12RCCommand::End()
{
	LOG("[PY12RCCommand] Ending" );

	this->pMotionProfiler->reset();
	CommandBase::pDriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void PY12RCCommand::Interrupted()
{
	LOG("[PY12RCCommand] Interrupted" );

	CommandBase::pDriveTrain->ResetDrive();

	return;
}
