#include "MPRobotCenterSwitchLeftCG.h"
#include "../RC2SLCommand.h"
#include "../SL2RCCommand.h"
#include "../RC2PY1Command.h"
#include "../PY12RCCommand.h"
#include "../../../Commands/Autonomous/MoveElevator.h"
#include "../../../Commands/Autonomous/ToggleIntake.h"
#include "../../../Commands/Autonomous/ToggleGripper.h"

/**
 *
 */MPRobotCenterSwitchLeftCG::MPRobotCenterSwitchLeftCG()
{
	AddSequential(new RC2SLCommand());
	AddSequential(new ToggleIntake( -1.00));

	AddParallel(new SL2RCCommand());
	AddSequential(new MoveElevator(  0.00));

	AddParallel(new RC2PY1Command());
	AddSequential(new ToggleGripper(-1.00));
	AddSequential(new ToggleIntake ( 1.00));

	AddParallel(new PY12RCCommand());
	AddSequential(new MoveElevator( 1.00));

	AddSequential(new RC2SLCommand());
	AddSequential(new ToggleIntake( -1.00));
}
