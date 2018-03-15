#include "MPRobotCenterSwitchRightCG.h"
#include "../Commands/RCtoSRCommand.h"
#include "../Commands/SRtoRCCommand.h"
#include "../Commands/RCtoPY1Command.h"
#include "../Commands/RCtoPY2Command.h"
#include "../Commands/PY1toRCCommand.h"
#include "../Commands/PY2toRCCommand.h"
#include "../../Commands/Autonomous/MoveElevator.h"
#include "../../Commands/Autonomous/ToggleIntake.h"
#include "../../Commands/Autonomous/ToggleGripper.h"

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
	AddSequential(new MoveElevator(Height::CUBE));

	// move to pyramid one position
	// open gripper
	AddParallel(new RCtoPY1Command());
	AddSequential(new ToggleGripper(Action::OPEN));
	
	// close gripper
	// intake cube
	AddParallel(new ToggleGripper(Action::CLOSE));
	AddSequential(new ToggleIntake (1.00));

	// move back to robot center
	// move elevator to switch position
	AddParallel(new PY1toRCCommand());
	AddSequential(new MoveElevator(Height::SWITCH));

	// move robot to switch right
	// eject cube
	AddSequential(new RCtoSRCommand());
	AddSequential(new ToggleIntake( -1.00));

	// THIRD CUBE
	// move back to robot center
	// move elevator to two cube height
	AddParallel(new SRtoRCCommand());
	AddSequential(new MoveElevator(Height::CUBEX2));

	// move to pyramid two position
	// open gripper
	AddParallel(new RCtoPY2Command());
	AddSequential(new ToggleGripper(Action::OPEN));
	
	// close gripper
	// intake cube
	AddParallel(new ToggleGripper(Action::CLOSE));
	AddSequential(new ToggleIntake (1.00));

	// move back to robot center
	// move elevator to switch height
	AddParallel(new PY2toRCCommand());
	AddSequential(new MoveElevator(Height::SWITCH));

	// move robot to switch right
	// eject cube
	AddSequential(new RCtoSRCommand());
	AddSequential(new ToggleIntake( -1.00));
}
