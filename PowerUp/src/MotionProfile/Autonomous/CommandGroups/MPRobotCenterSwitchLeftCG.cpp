#include "MPRobotCenterSwitchLeftCG.h"
#include "../RCtoSLCommand.h"
#include "../SLtoRCCommand.h"
#include "../RCtoPY1Command.h"
#include "../RCtoPY2Command.h"
#include "../PY1toRCCommand.h"
#include "../PY2toRCCommand.h"
#include "../../../Commands/Autonomous/MoveElevator.h"
#include "../../../Commands/Autonomous/ToggleIntake.h"
#include "../../../Commands/Autonomous/ToggleGripper.h"

/**
 *
 */
MPRobotCenterSwitchLeftCG::MPRobotCenterSwitchLeftCG()
{
	// first cube
	AddSequential(new RCtoSLCommand());
	AddSequential(new ToggleIntake( -1.00));

	// second cube
	AddParallel(new SLtoRCCommand());
	AddSequential(new MoveElevator(Elevator::Positions::CUBE));

	AddParallel(new RCtoPY1Command());
	AddSequential(new ToggleGripper(-1.00));
	AddSequential(new ToggleIntake ( 1.00));

	AddParallel(new PY1toRCCommand());
	AddSequential(new MoveElevator(Elevator::Positions::SWITCH));

	AddSequential(new RCtoSLCommand());
	AddSequential(new ToggleIntake( -1.00));

	// third cube
	AddParallel(new SLtoRCCommand());
	AddSequential(new MoveElevator(Elevator::Positions::CUBEX2));

	AddParallel(new RCtoPY2Command());
	AddSequential(new ToggleGripper(-1.00));
	AddSequential(new ToggleIntake ( 1.00));

	AddParallel(new PY2toRCCommand());
	AddSequential(new MoveElevator(Elevator::Positions::SWITCH));

	AddSequential(new RCtoSLCommand());
	AddSequential(new ToggleIntake( -1.00));
}
