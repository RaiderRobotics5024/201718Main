#include "RCtoPY1Command.h"
#include "../../Utilities/Log.h"

/**
 *
 */
RCtoPY1Command::RCtoPY1Command()
{
	LOG("[RCtoPY1Command] Constructed");

	if ( CommandBase::pDriveTrain != nullptr )
	{
		Requires(CommandBase::pDriveTrain);
		this->pMotionProfiler = new RCtoPY1Profile(*CommandBase::pDriveTrain->GetFrontLeftMotor());
	}
	else
	{
		LOG("[RCtoPY1Command] driveTrain is NULL");
	}

	return;
}

/**
 *
 */
RCtoPY1Command::~RCtoPY1Command()
{
	delete this->pMotionProfiler;

	return;
}

/**
 *
 */
void RCtoPY1Command::Initialize()
{
	LOG("[RCtoPY1Command] Initializing" );

	CommandBase::pDriveTrain->InitMotionProfiling();

	return;
}

/**
 *
 */
void RCtoPY1Command::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

	LOG("[RCtoPY1Command] Set Output: " << setOutput);

	CommandBase::pDriveTrain->GetFrontLeftMotor()->Set(ControlMode::MotionProfile, setOutput);

	this->pMotionProfiler->start();

	return;
}

/**
 *
 */
bool RCtoPY1Command::IsFinished()
{
	return false;
}

/**
 *
 */
void RCtoPY1Command::End()
{
	LOG("[RCtoPY1Command] Ending" );

	this->pMotionProfiler->reset();
	CommandBase::pDriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void RCtoPY1Command::Interrupted()
{
	LOG("[RCtoPY1Command] Interrupted" );

	CommandBase::pDriveTrain->ResetDrive();

	return;
}
