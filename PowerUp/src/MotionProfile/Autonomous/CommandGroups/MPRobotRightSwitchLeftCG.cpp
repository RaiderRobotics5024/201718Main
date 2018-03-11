#include "MPRobotRightSwitchLeftCG.h"
#include "../RRtoSLCommand.h"
#include "../../../Commands/Autonomous/MoveElevator.h"
#include "../../../Commands/Autonomous/ToggleIntake.h"
#include "../../../Commands/Autonomous/ToggleGripper.h"

/**
 *
 */
MPRobotRightSwitchLeftCG::MPRobotRightSwitchLeftCG()
{
	 // first cube
	AddSequential(new RRtoSLCommand());
	AddSequential(new ToggleIntake( -1.00));
}
