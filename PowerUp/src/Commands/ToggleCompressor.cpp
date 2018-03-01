#include <Commands/ToggleCompressor.h>
#include "../Utilities/Log.h"

/**
 *
 */
ToggleCompressor::ToggleCompressor()
{
	LOG("[CompressorToggle] Constructed");

	if (CommandBase::pCompressorSystem != nullptr)
	{
		Requires(CommandBase::pCompressorSystem);
	}
	else
	{
		LOG("[CompressorToggle] CompressorSystem is NULL!");
	}

	return;
}

/**
 *
 */
void ToggleCompressor::Initialize()
{
	LOG("[CompressorToggle] Initialized");

	return;
}

/**
 *
 */
void ToggleCompressor::Execute()
{
	frc::XboxController* pJoystick = CommandBase::pOI->GetJoystickOperator();

	if( pJoystick->GetStartButton())
	{
		CommandBase::pCompressorSystem->On();
	}

	if( pJoystick->GetBackButton())
	{
		CommandBase::pCompressorSystem->Off();
	}

	return;
}

/**
 *
 */
bool ToggleCompressor::IsFinished()
{
	return false;
}

/**
 *
 */
void ToggleCompressor::End()
{
	return;
}

/**
 *
 */
void ToggleCompressor::Interrupted()
{
	return;
}
