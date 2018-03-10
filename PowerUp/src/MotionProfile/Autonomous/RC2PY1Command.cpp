#include "RC2PY1Command.h"
#include "../../Utilities/Log.h"

/**
 *
 */
RC2PY1Command::RC2PY1Command()
{
	LOG("[RC2PY1Command] Constructed");

	if ( CommandBase::pDriveTrain != nullptr )
	{
		Requires(CommandBase::pDriveTrain);
		this->pMotionProfiler = new RC2PY1Profile(*CommandBase::pDriveTrain->GetFrontLeftMotor());
	}
	else
	{
		LOG("[RC2PY1Command] driveTrain is NULL");
	}

	return;
}

/**
 *
 */
void RC2PY1Command::Initialize()
{
	LOG("[RC2PY1Command] Initializing" );

	CommandBase::pDriveTrain->InitMotionProfiling();

	return;
}

/**
 *
 */
void RC2PY1Command::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

	LOG("[RC2PY1Command] Set Output: " << setOutput);

	CommandBase::pDriveTrain->GetFrontLeftMotor()->Set(ControlMode::MotionProfile, setOutput);

	this->pMotionProfiler->start();

	return;
}

/**
 *
 */
bool RC2PY1Command::IsFinished()
{
	return false;
}

/**
 *
 */
void RC2PY1Command::End()
{
	LOG("[RC2PY1Command] Ending" );

	this->pMotionProfiler->reset();
	CommandBase::pDriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void RC2PY1Command::Interrupted()
{
	LOG("[RC2PY1Command] Interrupted" );

	CommandBase::pDriveTrain->ResetDrive();

	return;
}
