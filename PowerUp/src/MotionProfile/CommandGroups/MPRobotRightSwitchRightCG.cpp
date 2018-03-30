#include "MPRobotRightSwitchRightCG.h"
#include "../Commands/RRtoSRCommand.h"
#include "../../Commands/Autonomous/ToggleIntake.h"
#include "../../Commands/Autonomous/ToggleGripper.h"

/**
 *
 */
MPRobotRightSwitchRightCG::MPRobotRightSwitchRightCG()
{
	 // first cube
	AddSequential(new RRtoSRCommand());
	AddSequential(new ToggleIntake( -1.00));
}
