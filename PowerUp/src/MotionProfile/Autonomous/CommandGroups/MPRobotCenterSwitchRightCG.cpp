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
	// FIRST CUBE
	// move from robot center to switch right
	// eject the cube
	AddSequential(new RCtoSRCommand());
	AddSequential(new ToggleIntake( -1.00));

	// SECOND CUBE
	// move from switch right to robot center
	// move elevator to one cube height
	AddParallel(new SRtoRCCommand());
	AddSequential(new MoveElevator(Elevator::Positions::CUBE));

	// move to pyramid one position
	// open gripper
	AddParallel(new RCtoPY1Command());
	AddSequential(new ToggleGripper(-1.00));
	
	// close gripper
	// intake cube
	AddParallel(new TogglerGripper(1.00));
	AddSequential(new ToggleIntake (1.00));

	// move back to robot center
	// move elevator to switch position
	AddParallel(new PY1toRCCommand());
	AddSequential(new MoveElevator(Elevator::Positions::SWITCH));

	// move robot to switch right
	// eject cube
	AddSequential(new RCtoSRCommand());
	AddSequential(new ToggleIntake( -1.00));

	// THIRD CUBE
	// move back to robot center
	// move elevator to two cube height
	AddParallel(new SRtoRCCommand());
	AddSequential(new MoveElevator(Elevator::Positions::CUBEX2));

	// move to pyramid two position
	// open gripper
	AddParallel(new RCtoPY2Command());
	AddSequential(new ToggleGripper(-1.00));
	
	// close gripper
	// intake cube
	AddParallel(new ToggleGripper(1.00));
	AddSequential(new ToggleIntake (1.00));

	// move back to robot center
	// move elevator to switch height
	AddParallel(new PY2toRCCommand());
	AddSequential(new MoveElevator(Elevator::Positions::SWITCH));

	// move robot to switch right
	// eject cube
	AddSequential(new RCtoSRCommand());
	AddSequential(new ToggleIntake( -1.00));
}
