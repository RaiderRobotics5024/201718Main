#include "RLtoSRCommand.h"
#include "../../Utilities/Log.h"

/**
 *
 */
RLtoSRCommand::RLtoSRCommand(Height::Type height)
{
	LOG("[RLtoSRCommand] Constructed");

	if ( CommandBase::pDriveTrain != nullptr )
	{
		Requires(CommandBase::pDriveTrain);
		this->pMotionProfiler = new RLtoSRProfile(*CommandBase::pDriveTrain->GetLeftFrontMotor(), *CommandBase::pDriveTrain->GetRightFrontMotor());
		this->htHeight = height;
	}
	else
	{
		LOG("[RLtoSRCommand] driveTrain is NULL");
	}

	this->pTimer = new Timer();

	return;
}

/**
 *
 */
RLtoSRCommand::~RLtoSRCommand()
{
	delete this->pTimer;
	delete this->pMotionProfiler;

	return;
}

/**
 *
 */
void RLtoSRCommand::Initialize()
{
	LOG("[RLtoSRCommand] Initializing" );

	this->pTimer->Reset();
	this->pTimer->Start();

	CommandBase::pDriveTrain->InitMotionProfilingMode();

	return;
}

/**
 *
 */
void RLtoSRCommand::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

	LOG("[RLtoSRCommand] Set Output: " << setOutput);

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
bool RLtoSRCommand::IsFinished()
{
	if (this->pTimer->Get() > 4.0) // stop after 4 seconds no matter what
	{
		LOG("[RLtoSRCommand] Timed out");

		return true;
	}

	if (this->pTimer->Get() > 0.5 && CommandBase::pDriveTrain->GetLeftFrontMotor()->GetActiveTrajectoryVelocity() == 0)
	{
		LOG("[RLtoSRCommand] MP Finished");

		return true;
	}

	if (this->pTimer->Get() > 0.5 && !CommandBase::pDriveTrain->IsDriving())
	{
		LOG("[RLtoSRCommand] MP Stopped");

		return true;
	}

	return false;
}

/**
 *
 */
void RLtoSRCommand::End()
{
	LOG("[RLtoSRCommand] Ending" );

	this->pMotionProfiler->reset();
	CommandBase::pDriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void RLtoSRCommand::Interrupted()
{
	LOG("[RLtoSRCommand] Interrupted" );

	this->pMotionProfiler->reset();
	CommandBase::pDriveTrain->ResetDrive();

	return;
}
