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

	return;
}

/**
 *
 */
void EjectCube::Initialize()
{
	LOG("[EjectCube] Initialized");

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
	CommandBase::pIntake->Reset();
	return true;
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

	return;
}
