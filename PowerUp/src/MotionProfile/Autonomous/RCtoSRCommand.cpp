#include "RCtoSRCommand.h"
#include "../../Utilities/Log.h"

/**
 *
 */
RCtoSRCommand::RCtoSRCommand()
{
	LOG("[RCtoSRCommand] Constructed");

	if ( CommandBase::pDriveTrain != nullptr )
	{
		Requires(CommandBase::pDriveTrain);
		this->pMotionProfiler = new RCtoSRProfile(*CommandBase::pDriveTrain->GetFrontLeftMotor());
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

	LOG("[RCtoSRCommand] SetValue: " << setOutput);

	CommandBase::pDriveTrain->GetFrontLeftMotor()->Set(ControlMode::MotionProfile, setOutput);

	this->pMotionProfiler->start();

	return;
}

/**
 *
 */
bool RCtoSRCommand::IsFinished()
{
	if (this->pTimer->Get() > 4.0) // stop after 4 seconds no matter what
	{
		LOG("[RCtoSRCommand] Timed out");

		return true;
	}

	if (this->pTimer->Get() > 0.5 && CommandBase::pDriveTrain->GetFrontLeftMotor()->GetActiveTrajectoryVelocity() == 0)
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

	CommandBase::pDriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void RCtoSRCommand::Trace()
{
	if (iCounter++ == 10)
	{
		CommandBase::pDriveTrain->Trace();

		LOG("[RCtoSRCommand] Current Target: " << CommandBase::pDriveTrain->GetLeftPosition()
				<< " Velocity: " << CommandBase::pDriveTrain->GetVelocity()
				<< " Time: "  << this->pTimer->Get());

		iCounter = 0;
	}

	return;
}
