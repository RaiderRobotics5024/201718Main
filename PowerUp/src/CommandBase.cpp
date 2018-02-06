#include "CommandBase.h"
#include "Subsystems/DriveTrain.h"

/**
 *
 */

DriveTrain* CommandBase::pDriveTrain = NULL;
OI* CommandBase::pOI = NULL;

CommandBase::CommandBase() : Command()
{
	std::cout << "[CommandBase] Constructed" << std::endl;

	init();
}

/**
 *
 */

CommandBase::~CommandBase()
{
	delete this->pDriveTrain;
	delete this->pOI;
}

/**
 *
 */

CommandBase::CommandBase(char const *name) : Command(name)
{
	std::cout << "[CommandBase] Constructed with name: " << name << std::endl;
}

/**
 *
 */

void CommandBase::init()
{
	std::cout << "[CommandBase] Initialized" << std::endl;

	if (pOI == nullptr) pOI = new OI();
	if (pDriveTrain == nullptr) pDriveTrain = new DriveTrain();
}
