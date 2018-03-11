#include "RCtoPY2Command.h"
#include "../../Utilities/Log.h"

/**
 *
 */
RCtoPY2Command::RCtoPY2Command()
{
	LOG("[RCtoPY2Command] Constructed");

	if ( CommandBase::pDriveTrain != nullptr )
	{
		Requires(CommandBase::pDriveTrain);
		this->pMotionProfiler = new RCtoPY2Profile(*CommandBase::pDriveTrain->GetFrontLeftMotor());
	}
	else
	{
		LOG("[RCtoPY2Command] driveTrain is NULL");
	}

	return;
}

/**
 *
 */
RCtoPY2Command::~RCtoPY2Command()
{
	delete this->pMotionProfiler;

	return;
}

/**
 *
 */
void RCtoPY2Command::Initialize()
{
	LOG("[RCtoPY2Command] Initializing" );

	CommandBase::pDriveTrain->InitMotionProfiling();

	return;
}

/**
 *
 */
void RCtoPY2Command::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

	LOG("[RCtoPY2Command] Set Output: " << setOutput);

	CommandBase::pDriveTrain->GetFrontLeftMotor()->Set(ControlMode::MotionProfile, setOutput);

	this->pMotionProfiler->start();

	return;
}

/**
 *
 */
bool RCtoPY2Command::IsFinished()
{
	return false;
}

/**
 *
 */
void RCtoPY2Command::End()
{
	LOG("[RCtoPY2Command] Ending" );

	this->pMotionProfiler->reset();
	CommandBase::pDriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void RCtoPY2Command::Interrupted()
{
	LOG("[RCtoPY2Command] Interrupted" );

	CommandBase::pDriveTrain->ResetDrive();

	return;
}
