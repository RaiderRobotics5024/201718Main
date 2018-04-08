#include "RLtoSLCommand.h"
#include "../../Utilities/Log.h"

/**
 *
 */
RLtoSLCommand::RLtoSLCommand(Height::Type height)
{
	LOG("[RLtoSLCommand] Constructed");

	if ( CommandBase::pDriveTrain != nullptr )
	{
		Requires(CommandBase::pDriveTrain);
		this->pMotionProfiler = new RLtoSLProfile(*CommandBase::pDriveTrain->GetLeftFrontMotor(), *CommandBase::pDriveTrain->GetRightFrontMotor());
		this->htHeight = height;
	}
	else
	{
		LOG("[RLtoSLCommand] driveTrain is NULL");
	}

	this->pTimer = new Timer();

	return;
}

/**
 *
 */
RLtoSLCommand::~RLtoSLCommand()
{
	delete this->pTimer;
	delete this->pMotionProfiler;

	return;
}

/**
 *
 */
void RLtoSLCommand::Initialize()
{
	LOG("[RLtoSLCommand] Initializing" );

	this->pTimer->Reset();
	this->pTimer->Start();

	CommandBase::pDriveTrain->InitMotionProfilingMode();

	return;
}

/**
 *
 */
void RLtoSLCommand::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

	LOG("[RLtoSLCommand] Set Output: " << setOutput);

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
bool RLtoSLCommand::IsFinished()
{
//	if (this->pTimer->Get() > 4.0) // stop after 4 seconds no matter what
//	{
//		LOG("[RLtoSLCommand] Timed out");
//
//		return true;
//	}

//	if (this->pTimer->Get() > 0.5 && CommandBase::pDriveTrain->GetLeftFrontMotor()->GetActiveTrajectoryVelocity() == 0)
//	{
//		LOG("[RLtoSLCommand] MP Finished");
//
//		return true;
//	}

//	if (this->pTimer->Get() > 0.5 && !CommandBase::pDriveTrain->IsDriving())
//	{
//		LOG("[RLtoSLCommand] MP Stopped");
//
//		return true;
//	}

	return false;
}

/**
 *
 */
void RLtoSLCommand::End()
{
	LOG("[RLtoSLCommand] Ending" );

	this->pMotionProfiler->reset();
	CommandBase::pDriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void RLtoSLCommand::Interrupted()
{
	LOG("[RLtoSLCommand] Interrupted" );

	this->pMotionProfiler->reset();
	CommandBase::pDriveTrain->ResetDrive();

	return;
}
