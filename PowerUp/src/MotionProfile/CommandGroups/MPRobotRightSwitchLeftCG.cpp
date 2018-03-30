#include "MPRobotRightSwitchLeftCG.h"
#include "../Commands/RRtoSLCommand.h"
#include "../../Commands/Autonomous/ElevatorService.h"
#include "../../Commands/Autonomous/ToggleIntake.h"
#include "../../Commands/Autonomous/ToggleGripper.h"

/**
 *
 */
MPRobotRightSwitchLeftCG::MPRobotRightSwitchLeftCG()
{
	// Start the elevator service. This handles calls from the other
	// commands to move the elevator.  It runs throughout autonomous mode
	AddParallel(new ElevatorService());

	// FIRST CUBE
	// move from robot right to switch left
	// eject the cube
	AddSequential(new RRtoSLCommand(Height::SWITCH));
	AddSequential(new ToggleIntake(Cube::EJECT));
}
