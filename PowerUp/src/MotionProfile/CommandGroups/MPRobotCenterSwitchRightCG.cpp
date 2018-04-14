#include "MPRobotCenterSwitchRightCG.h"
#include "../Commands/MIDtoPY1Command.h"
#include "../Commands/PY1toMIDCommand.h"
#include "../Commands/PY2toRCCommand.h"
#include "../Commands/RCtoSRCommand.h"
#include "../Commands/RCtoPY2Command.h"
#include "../Commands/SRtoMIDCommand.h"
#include "../../Commands/Autonomous/ElevatorService.h"
#include "../../Commands/Autonomous/ToggleIntake.h"
#include "../../Commands/Autonomous/ToggleGripper.h"

/**
 *
 */
MPRobotCenterSwitchRightCG::MPRobotCenterSwitchRightCG()
{
	// Start the elevator service. This handles calls from the other
	// commands to move the elevator.  It runs throughout autonomous mode
	AddParallel(new ElevatorService());

	// FIRST CUBE
	// move from robot center to switch right
	// eject the cube
	AddSequential(new RCtoSRCommand(Height::SWITCH));
	AddSequential(new ToggleIntake(Cube::EJECT));

	// SECOND CUBE
	// move from switch right to robot center
	// move elevator to one cube height
	AddSequential(new SRtoMIDCommand(Height::BOTTOM));

	// move to pyramid one position
	// open gripper
	AddParallel(new MIDtoPY1Command());
	AddSequential(new ToggleGripper(Action::OPEN));
	
	// close gripper
	// intake cube
	AddParallel(new ToggleGripper(Action::CLOSE));
	AddSequential(new ToggleIntake (Cube::TAKEIN));

	// move back to robot center
	// move elevator to switch position
	AddSequential(new PY1toMIDCommand(Height::SWITCH));

	// move robot to switch right
	// eject cube
	AddSequential(new RCtoSRCommand());
	AddSequential(new ToggleIntake(Cube::EJECT));

	// THIRD CUBE
	// move back to robot center
	// move elevator to two cube height
	AddSequential(new SRtoMIDCommand(Height::CUBEX2));

	// move to pyramid two position
	// open gripper
	AddParallel(new RCtoPY2Command());
	AddSequential(new ToggleGripper(Action::OPEN));
	
	// close gripper
	// intake cube
	AddParallel(new ToggleGripper(Action::CLOSE));
	AddSequential(new ToggleIntake (Cube::TAKEIN));

	// move back to robot center
	// move elevator to switch height
	AddSequential(new PY2toRCCommand(Height::SWITCH));

	// move robot to switch right
	// eject cube
	AddSequential(new RCtoSRCommand());
	AddSequential(new ToggleIntake(Cube::EJECT));
}
