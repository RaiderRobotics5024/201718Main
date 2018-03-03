#include "EjectCube.h"
#include "../Utilities/Log.h"
#include "../RobotMap.h"

/**
 * speed from -1 to 1
 */
EjectCube::EjectCube(double speed)
{
	LOG("[EjectCube] Constructed");

	if (CommandBase::pIntake != nullptr)
	{
		Requires(CommandBase::pIntake);
		this->dSpeed = speed;
	}
	else
	{
		LOG("[EjectCube] inTake is null!");
	}

	this->pTimer = new Timer();

	return;
}

/**
 *
 */
void EjectCube::Initialize()
{
	LOG("[EjectCube] Initialized");

	this->pTimer->Reset();
	this->pTimer->Start();

	CommandBase::pIntake->SetSpeed(dSpeed);

	return;
}

/**
 *
 */
void EjectCube::Execute()
{
	return;
}

/**
 *
 */
bool EjectCube::IsFinished()
{
	return this->pTimer->Get() > 2000;
}

/**
 *
 */
void EjectCube::End()
{
	LOG("[EjectCube] Ended");

	CommandBase::pIntake->Reset();

	return;
}

/**
 *
 */
void EjectCube::Interrupted()
{
	LOG("[EjectCube] Interrupted" );

	CommandBase::pIntake->Reset();

	return;
}
