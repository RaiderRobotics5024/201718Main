#include "MPRobotCenterSwitchRightCG.h"
#include "../RCtoSRCommand.h"
#include "../SRtoRCCommand.h"
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
MPRobotCenterSwitchRightCG::MPRobotCenterSwitchRightCG()
{
	 // first cube
	AddSequential(new RCtoSRCommand());
	AddSequential(new ToggleIntake( -1.00));

	// second cube
	AddParallel(new SRtoRCCommand());
	AddSequential(new MoveElevator(  0.00));

	AddParallel(new RCtoPY1Command());
	AddSequential(new ToggleGripper(-1.00));
	AddSequential(new ToggleIntake ( 1.00));

	AddParallel(new PY1toRCCommand());
	AddSequential(new MoveElevator( 2.00));

	AddSequential(new RCtoSRCommand());
	AddSequential(new ToggleIntake( -1.00));

	// third cube
	AddParallel(new SRtoRCCommand());
	AddSequential(new MoveElevator(  1.00));

	AddParallel(new RCtoPY2Command());
	AddSequential(new ToggleGripper(-1.00));
	AddSequential(new ToggleIntake ( 1.00));

	AddParallel(new PY2toRCCommand());
	AddSequential(new MoveElevator( 2.00));

	AddSequential(new RCtoSRCommand());
	AddSequential(new ToggleIntake( -1.00));
}
