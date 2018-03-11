#include "MPRobotCenterSwitchLeftCG.h"
#include "../RCtoSLCommand.h"
#include "../SLtoRCCommand.h"
#include "../RCtoPY1Command.h"
#include "../PY1toRCCommand.h"
#include "../../../Commands/Autonomous/MoveElevator.h"
#include "../../../Commands/Autonomous/ToggleIntake.h"
#include "../../../Commands/Autonomous/ToggleGripper.h"

/**
 *
 */MPRobotCenterSwitchLeftCG::MPRobotCenterSwitchLeftCG()
{
	AddSequential(new RCtoSLCommand());
	AddSequential(new ToggleIntake( -1.00));

	AddParallel(new SLtoRCCommand());
	AddSequential(new MoveElevator(  0.00));

	AddParallel(new RCtoPY1Command());
	AddSequential(new ToggleGripper(-1.00));
	AddSequential(new ToggleIntake ( 1.00));

	AddParallel(new PY1toRCCommand());
	AddSequential(new MoveElevator( 1.00));

	AddSequential(new RCtoSLCommand());
	AddSequential(new ToggleIntake( -1.00));
}
