#include "RC2SRCommand.h"
#include "../../Utilities/Log.h"

/**
 *
 */
RC2SRCommand::RC2SRCommand()
{
	LOG("[RC2SRCommand] Constructed");

	if ( CommandBase::pDriveTrain != nullptr )
	{
		Requires(CommandBase::pDriveTrain);
		this->pMotionProfiler = new RC2SRProfile(*CommandBase::pDriveTrain->GetFrontLeftMotor());
	}
	else
	{
		LOG("[RC2SRCommand] driveTrain is NULL");
	}

	return;
}

/**
 *
 */
void RC2SRCommand::Initialize()
{
	LOG("[RC2SRCommand] Initializing" );

	CommandBase::pDriveTrain->InitMotionProfiling();

	return;
}

/**
 *
 */
void RC2SRCommand::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

	LOG("[RC2SRCommand] Set Output: " << setOutput);

	CommandBase::pDriveTrain->GetFrontLeftMotor()->Set(ControlMode::MotionProfile, setOutput);

	this->pMotionProfiler->start();

	return;
}

/**
 *
 */
bool RC2SRCommand::IsFinished()
{
	return false;
}

/**
 *
 */
void RC2SRCommand::End()
{
	LOG("[RC2SRCommand] Ending" );

	this->pMotionProfiler->reset();
	CommandBase::pDriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void RC2SRCommand::Interrupted()
{
	LOG("[RC2SRCommand] Interrupted" );

	CommandBase::pDriveTrain->ResetDrive();

	return;
}
