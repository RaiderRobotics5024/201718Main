#include "../Utilities/Log.h"
#include <Commands/ToggleCompressor.h>
#include <Subsystems/CompressorSystem.h>

/**
 *
 */
CompressorSystem::CompressorSystem() : Subsystem("Compressor")
{
	LOG("[CompressorSystem] Constructed");

	this->pCompressor = new Compressor(COMPRESSOR_ID);

	return;
}

/**
 *
 */
CompressorSystem::~CompressorSystem()
{
	delete this->pCompressor;

	return;
}

/**
 *
 */
void CompressorSystem::InitDefaultCommand()
{
	LOG("[CompressorSystem] Initilized Default Command");

	SetDefaultCommand(new ToggleCompressor());

	return;
}

/**
 *
 */
void CompressorSystem::Off(void)
{
	LOG("[CompressorSystem] Turning compressor off");

	this->pCompressor->SetClosedLoopControl(false);

	return;
}

/**
 *
 */
void CompressorSystem::On(void)
{
	LOG("[CompressorSystem] Turning compressor on");

	this->pCompressor->SetClosedLoopControl(true);

	return;
}
