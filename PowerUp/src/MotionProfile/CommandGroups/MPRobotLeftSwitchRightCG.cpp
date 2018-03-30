#include "MPRobotLeftSwitchRightCG.h"
#include "../Commands/RLtoSRCommand.h"
#include "../../Commands/Autonomous/ToggleIntake.h"
#include "../../Commands/Autonomous/ToggleGripper.h"

/**
 *
 */
MPRobotLeftSwitchRightCG::MPRobotLeftSwitchRightCG()
{
	 // first cube
	AddSequential(new RLtoSRCommand());
	AddSequential(new ToggleIntake( -1.00));
}
