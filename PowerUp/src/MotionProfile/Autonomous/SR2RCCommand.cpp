#include "SR2RCCommand.h"
#include "../../Utilities/Log.h"

/**
 *
 */
SR2RCCommand::SR2RCCommand()
{
	LOG("[SR2RCCommand] Constructed");

	if ( CommandBase::pDriveTrain != nullptr )
	{
		Requires(CommandBase::pDriveTrain);
		this->pMotionProfiler = new SR2RCProfile(*CommandBase::pDriveTrain->GetFrontLeftMotor());
	}
	else
	{
		LOG("[SR2RCCommand] driveTrain is NULL");
	}

	return;
}

/**
 *
 */
void SR2RCCommand::Initialize()
{
	LOG("[SR2RCCommand] Initializing" );

	CommandBase::pDriveTrain->InitMotionProfiling();

	return;
}

/**
 *
 */
void SR2RCCommand::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

	LOG("[SR2RCCommand] Set Output: " << setOutput);

	CommandBase::pDriveTrain->GetFrontLeftMotor()->Set(ControlMode::MotionProfile, setOutput);

	this->pMotionProfiler->start();

	return;
}

/**
 *
 */
bool SR2RCCommand::IsFinished()
{
	return false;
}

/**
 *
 */
void SR2RCCommand::End()
{
	LOG("[SR2RCCommand] Ending" );

	this->pMotionProfiler->reset();
	CommandBase::pDriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void SR2RCCommand::Interrupted()
{
	LOG("[SR2RCCommand] Interrupted" );

	CommandBase::pDriveTrain->ResetDrive();

	return;
}
