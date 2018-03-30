#include "MPRobotLeftSwitchRightCG.h"
#include "../Commands/RLtoSRCommand.h"
#include "../../Commands/Autonomous/ElevatorService.h"
#include "../../Commands/Autonomous/ToggleIntake.h"
#include "../../Commands/Autonomous/ToggleGripper.h"

/**
 *
 */
MPRobotLeftSwitchRightCG::MPRobotLeftSwitchRightCG()
{
	// Start the elevator service. This handles calls from the other
	// commands to move the elevator.  It runs throughout autonomous mode
	AddParallel(new ElevatorService());

	// FIRST CUBE
	// move from robot left to switch right
	// eject the cube
	AddSequential(new RLtoSRCommand(Height::SWITCH));
	AddSequential(new ToggleIntake(Cube::EJECT));
}
