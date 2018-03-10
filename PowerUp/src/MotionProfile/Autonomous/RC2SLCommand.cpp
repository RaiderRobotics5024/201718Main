#include "RC2SLCommand.h"
#include "../../Utilities/Log.h"

/**
 *
 */
RC2SLCommand::RC2SLCommand()
{
	LOG("[RC2SLCommand] Constructed");

	if ( CommandBase::pDriveTrain != nullptr )
	{
		Requires(CommandBase::pDriveTrain);
		this->pMotionProfiler = new RC2SLProfile(*CommandBase::pDriveTrain->GetFrontLeftMotor());
	}
	else
	{
		LOG("[RC2SLCommand] driveTrain is NULL");
	}

	return;
}

/**
 *
 */
void RC2SLCommand::Initialize()
{
	LOG("[RC2SLCommand] Initializing" );

	CommandBase::pDriveTrain->InitMotionProfiling();

	return;
}

/**
 *
 */
void RC2SLCommand::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

	LOG("[RC2SLCommand] Set Output: " << setOutput);

	CommandBase::pDriveTrain->GetFrontLeftMotor()->Set(ControlMode::MotionProfile, setOutput);

	this->pMotionProfiler->start();

	return;
}

/**
 *
 */
bool RC2SLCommand::IsFinished()
{
	return false;
}

/**
 *
 */
void RC2SLCommand::End()
{
	LOG("[RC2SLCommand] Ending" );

	this->pMotionProfiler->reset();
	CommandBase::pDriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void RC2SLCommand::Interrupted()
{
	LOG("[RC2SLCommand] Interrupted" );

	CommandBase::pDriveTrain->ResetDrive();

	return;
}
