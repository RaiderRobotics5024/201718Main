#include "PY2toRCCommand.h"
#include "../../Utilities/Log.h"

/**
 *
 */
PY2toRCCommand::PY2toRCCommand()
{
	LOG("[PY2toRCCommand] Constructed");

	if ( CommandBase::pDriveTrain != nullptr )
	{
		Requires(CommandBase::pDriveTrain);
		this->pMotionProfiler = new PY2toRCProfile(*CommandBase::pDriveTrain->GetFrontLeftMotor());
	}
	else
	{
		LOG("[PY2toRCCommand] driveTrain is NULL");
	}

	return;
}

/**
 *
 */
PY2toRCCommand::~PY2toRCCommand()
{
	delete this->pMotionProfiler;

	return;
}

/**
 *
 */
void PY2toRCCommand::Initialize()
{
	LOG("[PY2toRCCommand] Initializing" );

	CommandBase::pDriveTrain->InitMotionProfiling();

	return;
}

/**
 *
 */
void PY2toRCCommand::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

	LOG("[PY2toRCCommand] Set Output: " << setOutput);

	CommandBase::pDriveTrain->GetFrontLeftMotor()->Set(ControlMode::MotionProfile, setOutput);

	this->pMotionProfiler->start();

	return;
}

/**
 *
 */
bool PY2toRCCommand::IsFinished()
{
	return false;
}

/**
 *
 */
void PY2toRCCommand::End()
{
	LOG("[PY2toRCCommand] Ending" );

	this->pMotionProfiler->reset();
	CommandBase::pDriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void PY2toRCCommand::Interrupted()
{
	LOG("[PY2toRCCommand] Interrupted" );

	CommandBase::pDriveTrain->ResetDrive();

	return;
}
