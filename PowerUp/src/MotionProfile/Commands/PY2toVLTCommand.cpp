#include "PY2toVLTCommand.h"
#include "../../Utilities/Log.h"

/**
 *
 */
PY2toVLTCommand::PY2toVLTCommand(Height::Type height)
{
	LOG("[PY2toVLTCommand] Constructed");

	if ( CommandBase::pDriveTrain != nullptr )
	{
		Requires(CommandBase::pDriveTrain);
		this->pMotionProfiler = new PY2toVLTProfile(*CommandBase::pDriveTrain->GetLeftFrontMotor(), *CommandBase::pDriveTrain->GetRightFrontMotor());
		this->htHeight = height;
	}
	else
	{
		LOG("[PY2toVLTCommand] driveTrain is NULL");
	}

	this->pTimer = new Timer();

	return;
}

/**
 *
 */
PY2toVLTCommand::~PY2toVLTCommand()
{
	delete this->pTimer;
	delete this->pMotionProfiler;

	return;
}

/**
 *
 */
void PY2toVLTCommand::Initialize()
{
	LOG("[PY2toRCCommand] Initializing" );

	this->pTimer->Reset();
	this->pTimer->Start();

	CommandBase::pDriveTrain->InitMotionProfilingMode();

	return;
}

/**
 *
 */
void PY2toVLTCommand::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

	LOG("[PY2toVLTCommand] Set Output: " << setOutput);

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
bool PY2toVLTCommand::IsFinished()
{
	if (this->pTimer->Get() > 4.0) // stop after 4 seconds no matter what
	{
		LOG("[PY2toVLTCommand] Timed out");

		return true;
	}

	if (this->pTimer->Get() > 0.5 && CommandBase::pDriveTrain->GetLeftFrontMotor()->GetActiveTrajectoryVelocity() == 0)
	{
		LOG("[PY2toVLTCommand] MP Finished");

		return true;
	}

	if (this->pTimer->Get() > 0.5 && !CommandBase::pDriveTrain->IsDriving())
	{
		LOG("[PY2toVLTCommand] MP Stopped");

		return true;
	}

	return false;
}

/**
 *
 */
void PY2toVLTCommand::End()
{
	LOG("[PY2toVLTCommand] Ending" );

	this->pMotionProfiler->reset();
	CommandBase::pDriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void PY2toVLTCommand::Interrupted()
{
	LOG("[PY2toVLTCommand] Interrupted" );

	this->pMotionProfiler->reset();
	CommandBase::pDriveTrain->ResetDrive();

	return;
}
