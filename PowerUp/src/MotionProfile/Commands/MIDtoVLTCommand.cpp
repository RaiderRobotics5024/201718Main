#include "MIDtoVLTCommand.h"
#include "../../Utilities/Log.h"

/**
 *
 */
MIDtoVLTCommand::MIDtoVLTCommand(Height::Type height)
{
	LOG("[MIDtoVLTCommand] Constructed");

	if ( CommandBase::pDriveTrain != nullptr )
	{
		Requires(CommandBase::pDriveTrain);
		this->pMotionProfiler = new MIDtoVLTProfile(*CommandBase::pDriveTrain->GetLeftFrontMotor(), *CommandBase::pDriveTrain->GetRightFrontMotor());
		this->htHeight = height;
	}
	else
	{
		LOG("[MIDtoVLTCommand] driveTrain is NULL");
	}

	this->pTimer = new Timer();

	return;
}

/**
 *
 */
MIDtoVLTCommand::~MIDtoVLTCommand()
{
	delete this->pTimer;
	delete this->pMotionProfiler;

	return;
}

/**
 *
 */
void MIDtoVLTCommand::Initialize()
{
	LOG("[MIDtoRCCommand] Initializing" );

	this->pTimer->Reset();
	this->pTimer->Start();

	CommandBase::pDriveTrain->InitMotionProfilingMode();

	return;
}

/**
 *
 */
void MIDtoVLTCommand::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

	LOG("[MIDtoVLTCommand] Set Output: " << setOutput);

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
bool MIDtoVLTCommand::IsFinished()
{
	if (this->pMotionProfiler->isFinished())
	{
		LOG("[MIDtoVLTCommand] MP Finished");

		return true;
	}

	return false;
}

/**
 *
 */
void MIDtoVLTCommand::End()
{
	LOG("[MIDtoVLTCommand] Ending" );

	this->pMotionProfiler->reset();
	CommandBase::pDriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void MIDtoVLTCommand::Interrupted()
{
	LOG("[MIDtoVLTCommand] Interrupted" );

	this->pMotionProfiler->reset();
	CommandBase::pDriveTrain->ResetDrive();

	return;
}
