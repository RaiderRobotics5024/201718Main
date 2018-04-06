#include "RCtoSRCommand.h"
#include "../../Utilities/Log.h"

/**
 *
 */
RCtoSRCommand::RCtoSRCommand(Height::Type height)
{
	LOG("[RCtoSRCommand] Constructed");

	if ( CommandBase::pDriveTrain != nullptr )
	{
		Requires(CommandBase::pDriveTrain);
		this->pMotionProfiler = new RCtoSRProfile(*CommandBase::pDriveTrain->GetLeftFrontMotor(), *CommandBase::pDriveTrain->GetRightFrontMotor());
		this->htHeight = height;
	}
	else
	{
		LOG("[RCtoSRCommand] driveTrain is NULL");
	}

	this->pTimer = new Timer();

	return;
}

/**
 *
 */
RCtoSRCommand::~RCtoSRCommand()
{
	delete this->pTimer;
	delete this->pMotionProfiler;

	return;
}

/**
 *
 */
void RCtoSRCommand::Initialize()
{
	LOG("[RCtoSRCommand] Initializing" );

	this->pTimer->Reset();
	this->pTimer->Start();

	CommandBase::pDriveTrain->InitMotionProfiling();

	return;
}

/**
 *
 */
void RCtoSRCommand::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

//	LOG("[RCtoSRCommand] SetValue: " << setOutput);

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
bool RCtoSRCommand::IsFinished()
{
//	if (this->pTimer->Get() > 4.0) // stop after 4 seconds no matter what
//	{
//		LOG("[RCtoSRCommand] Timed out");
//
//		return true;
//	}

	if (this->pTimer->Get() > 0.5 && CommandBase::pDriveTrain->GetLeftFrontMotor()->GetActiveTrajectoryVelocity() == 0)
	{
		LOG("[RCtoSRCommand] MP Finished");

		return true;
	}

	if (this->pTimer->Get() > 0.5 && !CommandBase::pDriveTrain->IsDriving())
	{
		LOG("[RCtoSRCommand] MP Stopped");

		return true;
	}

	return false;
}

/**
 *
 */
void RCtoSRCommand::End()
{
	LOG("[RCtoSRCommand] Ending" );

	this->pMotionProfiler->reset();
	CommandBase::pDriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void RCtoSRCommand::Interrupted()
{
	LOG("[RCtoSRCommand] Interrupted" );

	this->pMotionProfiler->reset();
	CommandBase::pDriveTrain->ResetDrive();

	return;
}
