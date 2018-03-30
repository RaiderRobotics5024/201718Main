#include "PY2toRCCommand.h"
#include "../../Utilities/Log.h"

/**
 *
 */
PY2toRCCommand::PY2toRCCommand(Height::Type height)
{
	LOG("[PY2toRCCommand] Constructed");

	if ( CommandBase::pDriveTrain != nullptr )
	{
		Requires(CommandBase::pDriveTrain);
		this->pMotionProfiler = new PY2toRCProfile(*CommandBase::pDriveTrain->GetLeftFrontMotor(), *CommandBase::pDriveTrain->GetRightFrontMotor());
		this->htHeight = height;
	}
	else
	{
		LOG("[PY2toRCCommand] driveTrain is NULL");
	}

	this->pTimer = new Timer();

	return;
}

/**
 *
 */
PY2toRCCommand::~PY2toRCCommand()
{
	delete this->pTimer;
	delete this->pMotionProfiler;

	return;
}

/**
 *
 */
void PY2toRCCommand::Initialize()
{
	LOG("[PY2toRCCommand] Initializing" );

	this->pTimer->Reset();
	this->pTimer->Start();

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

	CommandBase::pDriveTrain->GetLeftFrontMotor()->Set(ControlMode::MotionProfile, setOutput);
	CommandBase::pDriveTrain->GetRightFrontMotor()->Set(ControlMode::MotionProfile, setOutput);

	this->pMotionProfiler->start();

	// ask elevator service to move to our set height
	gElevatorHeight = this->htHeight;

	return;
}

/**
 *
 */
bool PY2toRCCommand::IsFinished()
{
	if (this->pTimer->Get() > 4.0) // stop after 4 seconds no matter what
	{
		LOG("[PY2toRCCommand] Timed out");

		return true;
	}

	if (this->pTimer->Get() > 0.5 && CommandBase::pDriveTrain->GetLeftFrontMotor()->GetActiveTrajectoryVelocity() == 0)
	{
		LOG("[PY2toRCCommand] MP Finished");

		return true;
	}

	if (this->pTimer->Get() > 0.5 && !CommandBase::pDriveTrain->IsDriving())
	{
		LOG("[PY2toRCCommand] MP Stopped");

		return true;
	}

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

	this->pMotionProfiler->reset();
	CommandBase::pDriveTrain->ResetDrive();

	return;
}
