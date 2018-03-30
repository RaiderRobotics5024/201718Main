#include "MPRobotLeftSwitchLeftCG.h"
#include "../Commands/RLtoSLCommand.h"
#include "../../Commands/Autonomous/ElevatorService.h"
#include "../../Commands/Autonomous/ToggleIntake.h"
#include "../../Commands/Autonomous/ToggleGripper.h"

/**
 *
 */
MPRobotLeftSwitchLeftCG::MPRobotLeftSwitchLeftCG()
{
	// Start the elevator service. This handles calls from the other
	// commands to move the elevator.  It runs throughout autonomous mode
	AddParallel(new ElevatorService());

	// FIRST CUBE
	// move from robot left to switch left
	// eject the cube
	AddSequential(new RLtoSLCommand(Height::SWITCH));
	AddSequential(new ToggleIntake(Cube::EJECT));
}
