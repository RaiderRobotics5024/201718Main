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
	frc::XboxController* pJoyOperator = CommandBase::pOI->GetJoystickOperator();

	if( pJoyOperator->GetStartButton())
	{
		CommandBase::pCompressorSystem->On();
	}

	if( pJoyOperator->GetBackButton())
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
