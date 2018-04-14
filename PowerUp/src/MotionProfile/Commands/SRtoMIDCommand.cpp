#include "SRtoMIDCommand.h"
#include "../../Utilities/Log.h"

/**
 *
 */
SRtoMIDCommand::SRtoMIDCommand(Height::Type height)
{
	LOG("[SRtoMIDCommand] Constructed");

	if ( CommandBase::pDriveTrain != nullptr )
	{
		Requires(CommandBase::pDriveTrain);
		this->pMotionProfiler = new SRtoMIDProfile(*CommandBase::pDriveTrain->GetLeftFrontMotor(), *CommandBase::pDriveTrain->GetRightFrontMotor());
		this->htHeight = height;
	}
	else
	{
		LOG("[SRtoMIDCommand] driveTrain is NULL");
	}

	this->pTimer = new Timer();

	return;
}

/**
 *
 */
SRtoMIDCommand::~SRtoMIDCommand()
{
	delete this->pTimer;
	delete this->pMotionProfiler;

	return;
}

/**
 *
 */
void SRtoMIDCommand::Initialize()
{
	LOG("[SRtoMIDCommand] Initializing" );

	this->pTimer->Reset();
	this->pTimer->Start();

	CommandBase::pDriveTrain->InitMotionProfilingMode();

	return;
}

/**
 *
 */
void SRtoMIDCommand::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

//	LOG("[SRtoMIDCommand] Set Output: " << setOutput);

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
bool SRtoMIDCommand::IsFinished()
{
	if (this->pMotionProfiler->isFinished())
	{
		LOG("[RCtoSRCommand] MP Finished");

		return true;
	}

	return false;
}

/**
 *
 */
void SRtoMIDCommand::End()
{
	LOG("[SRtoMIDCommand] Ending: " << this->pTimer->Get());

	this->pMotionProfiler->reset();
	CommandBase::pDriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void SRtoMIDCommand::Interrupted()
{
	LOG("[SRtoMIDCommand] Interrupted" );

	this->pMotionProfiler->reset();
	CommandBase::pDriveTrain->ResetDrive();

	return;
}
