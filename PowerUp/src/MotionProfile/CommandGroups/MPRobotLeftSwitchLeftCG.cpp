#include "MPRobotLeftSwitchLeftCG.h"
#include "../Commands/RLtoSLCommand.h"
#include "../../Commands/Autonomous/MoveElevator.h"
#include "../../Commands/Autonomous/ToggleIntake.h"
#include "../../Commands/Autonomous/ToggleGripper.h"

/**
 *
 */
MPRobotLeftSwitchLeftCG::MPRobotLeftSwitchLeftCG()
{
	 // first cube
	AddSequential(new RLtoSLCommand());
	AddSequential(new ToggleIntake( -1.00));
}
