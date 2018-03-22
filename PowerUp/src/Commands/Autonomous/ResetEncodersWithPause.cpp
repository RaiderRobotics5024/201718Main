#include "ResetEncodersWithPause.h"
#include "../../Utilities/Log.h"
#include "../../RobotMap.h"

/**
 * distance in inches, speed from -1 to 1
 */
ResetEncodersWithPause::ResetEncodersWithPause(double timeToPauseInSeconds)
{
	LOG("[ResetEncodersWithPause] Constructed: " << (unsigned int)this );

	if (CommandBase::pDriveTrain != nullptr)
	{
		Requires(CommandBase::pDriveTrain);
	}
	else
	{
		LOG("[ResetEncodersWithPause] driveTrain is null!");
	}

	this->pTimer = new frc::Timer();

	this->m_timeToPauseInSeconds = timeToPauseInSeconds;

	return;
}

/**
 *
 */
ResetEncodersWithPause::~ResetEncodersWithPause()
{
	delete this->pTimer;
}

/**
 *
 */
void ResetEncodersWithPause::Initialize()
{

	LOG("[ResetEncodersWithPause] Initialized with time: " << this->m_timeToPauseInSeconds << " seconds.") ;

	this->pTimer->Reset();
	this->pTimer->Start();

	CommandBase::pDriveTrain->ResetEncoders();

	return;
}

/**
 *
 */
void ResetEncodersWithPause::Execute()
{
	// Does nothing... smarts in IsFinished()

	return;
}

/**
 *
 */
bool ResetEncodersWithPause::IsFinished()
{
	if ( this->pTimer->Get() >= this->m_timeToPauseInSeconds )
	{
		LOG("[ResetEncodersWithPause] waited " << this->m_timeToPauseInSeconds << " seconds.");
		return true;
	}

	return false;
}

/**
 *
 */
void ResetEncodersWithPause::End()
{
	LOG("[DriveWithEncoders] Ended " << (unsigned int)this);

	return;
}

/**
 *
 */
void ResetEncodersWithPause::Interrupted()
{
	LOG("[DriveWithEncoders] Interrupted" );

	return;
}
