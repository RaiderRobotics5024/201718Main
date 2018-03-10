#include "MPRobotCenterSwitchRightCG.h"
#include "../RC2SRCommand.h"
#include "../SR2RCCommand.h"
#include "../RC2PY1Command.h"
#include "../PY12RCCommand.h"
#include "../../../Commands/Autonomous/MoveElevator.h"
#include "../../../Commands/Autonomous/ToggleIntake.h"
#include "../../../Commands/Autonomous/ToggleGripper.h"

/**
 *
 */MPRobotCenterSwitchRightCG::MPRobotCenterSwitchRightCG()
{
	AddSequential(new RC2SRCommand());
	AddSequential(new ToggleIntake( -1.00));

	AddParallel(new SR2RCCommand());
	AddSequential(new MoveElevator(  0.00));

	AddParallel(new RC2PY1Command());
	AddSequential(new ToggleGripper(-1.00));
	AddSequential(new ToggleIntake ( 1.00));

	AddParallel(new PY12RCCommand());
	AddSequential(new MoveElevator( 1.00));

	AddSequential(new RC2SRCommand());
	AddSequential(new ToggleIntake( -1.00));

	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.

	// To run multiple commands at the same time,
	// use AddParallel()
	// e.g. AddParallel(new Command1());
	//      AddSequential(new Command2());
	// Command1 and Command2 will run in parallel.

	// A command group will require all of the subsystems that each member
	// would require.
	// e.g. if Command1 requires chassis, and Command2 requires arm,
	// a CommandGroup containing them would require both the chassis and the
	// arm.
}
