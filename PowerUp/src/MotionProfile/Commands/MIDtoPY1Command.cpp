#include "MIDtoPY1Command.h"
#include "../../Utilities/Log.h"

/**
 *
 */
MIDtoPY1Command::MIDtoPY1Command(Height::Type height)
{
	LOG("[MIDtoPY1Command] Constructed");

	if ( CommandBase::pDriveTrain != nullptr )
	{
		Requires(CommandBase::pDriveTrain);
		this->pMotionProfiler = new MIDtoPY1Profile(*CommandBase::pDriveTrain->GetLeftFrontMotor(), *CommandBase::pDriveTrain->GetRightFrontMotor());
		this->htHeight = height;
	}
	else
	{
		LOG("[MIDtoPY1Command] driveTrain is NULL");
	}

	this->pTimer = new Timer();

	return;
}

/**
 *
 */
MIDtoPY1Command::~MIDtoPY1Command()
{
	delete this->pTimer;
	delete this->pMotionProfiler;

	return;
}

/**
 *
 */
void MIDtoPY1Command::Initialize()
{
	LOG("[MIDtoPY1Command] Initializing" );

	this->pTimer->Reset();
	this->pTimer->Start();

	CommandBase::pDriveTrain->InitMotionProfilingMode();

	return;
}

/**
 *
 */
void MIDtoPY1Command::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

//	LOG("[MIDtoPY1Command] Set Output: " << setOutput);

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
bool MIDtoPY1Command::IsFinished()
{
	if (this->pMotionProfiler->isFinished())
	{
		LOG("[MIDtoPY1Command] MP Finished");

		return true;
	}

	return false;
}

/**
 *
 */
void MIDtoPY1Command::End()
{
	LOG("[MIDtoPY1Command] Ending" );

	this->pMotionProfiler->reset();
	CommandBase::pDriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void MIDtoPY1Command::Interrupted()
{
	LOG("[MIDtoPY1Command] Interrupted" );

	this->pMotionProfiler->reset();
	CommandBase::pDriveTrain->ResetDrive();

	return;
}
