#include "PY1toRCCommand.h"
#include "../../Utilities/Log.h"

/**
 *
 */
PY1toRCCommand::PY1toRCCommand()
{
	LOG("[PY1toRCCommand] Constructed");

	if ( CommandBase::pDriveTrain != nullptr )
	{
		Requires(CommandBase::pDriveTrain);
		this->pMotionProfiler = new PY1toRCProfile(*CommandBase::pDriveTrain->GetFrontLeftMotor());
	}
	else
	{
		LOG("[PY1toRCCommand] driveTrain is NULL");
	}

	return;
}

/**
 *
 */
PY1toRCCommand::~PY1toRCCommand()
{
	delete this->pMotionProfiler;

	return;
}

/**
 *
 */
void PY1toRCCommand::Initialize()
{
	LOG("[PY1toRCCommand] Initializing" );

	CommandBase::pDriveTrain->InitMotionProfiling();

	return;
}

/**
 *
 */
void PY1toRCCommand::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

	LOG("[PY1toRCCommand] Set Output: " << setOutput);

	CommandBase::pDriveTrain->GetFrontLeftMotor()->Set(ControlMode::MotionProfile, setOutput);

	this->pMotionProfiler->start();

	return;
}

/**
 *
 */
bool PY1toRCCommand::IsFinished()
{
	return false;
}

/**
 *
 */
void PY1toRCCommand::End()
{
	LOG("[PY1toRCCommand] Ending" );

	this->pMotionProfiler->reset();
	CommandBase::pDriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void PY1toRCCommand::Interrupted()
{
	LOG("[PY1toRCCommand] Interrupted" );

	CommandBase::pDriveTrain->ResetDrive();

	return;
}
