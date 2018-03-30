#include "MPRobotRightSwitchRightCG.h"
#include "../Commands/RRtoSRCommand.h"
#include "../../Commands/Autonomous/ElevatorService.h"
#include "../../Commands/Autonomous/ToggleIntake.h"
#include "../../Commands/Autonomous/ToggleGripper.h"

/**
 *
 */
MPRobotRightSwitchRightCG::MPRobotRightSwitchRightCG()
{
	// FIRST CUBE
	// move from robot right to switch right
	// eject the cube
	AddSequential(new RRtoSRCommand(Height::SWITCH));
	AddSequential(new ToggleIntake(Cube::EJECT));
}
