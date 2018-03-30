#include "MPRobotCenterSwitchLeftCG.h"
#include "../Commands/RCtoSLCommand.h"
#include "../Commands/SLtoRCCommand.h"
#include "../Commands/RCtoPY1Command.h"
#include "../Commands/RCtoPY2Command.h"
#include "../Commands/PY1toRCCommand.h"
#include "../Commands/PY2toRCCommand.h"
#include "../../Commands/Autonomous/ElevatorService.h"
#include "../../Commands/Autonomous/ToggleIntake.h"
#include "../../Commands/Autonomous/ToggleGripper.h"

/**
 *
 */
MPRobotCenterSwitchLeftCG::MPRobotCenterSwitchLeftCG()
{
	// Start the elevator service. This handles calls from the other
	// commands to move the elevator.  It runs throughout autonomous mode
	AddParallel(new ElevatorService());

	// FIRST CUBE
	// move from robot center to switch left
	// eject the cube
	AddSequential(new RCtoSLCommand(Height::SWITCH));
	AddSequential(new ToggleIntake(Cube::EJECT));

	// SECOND CUBE
	// move from switch left back to robot center
	// set elevator height to cube one
	AddSequential(new SLtoRCCommand(Height::BOTTOM));

	// move robot to pyramid 1 position
	// open the gripper
	AddParallel(new RCtoPY1Command());
	AddSequential(new ToggleGripper(Action::OPEN));
	
	// close the gripper
	// intake the cube
	AddParallel(new ToggleGripper(Action::CLOSE));
	AddSequential(new ToggleIntake (Cube::TAKEIN));

	// move robot back to robot center
	// set elevator height to switch
	AddSequential(new PY1toRCCommand(Height::SWITCH));

	// move robot from robot center to switch left
	// eject the cube
	AddSequential(new RCtoSLCommand());
	AddSequential(new ToggleIntake(Cube::EJECT));

	// THIRD CUBE
	// move robot from switch left back to robot center
	// set elevator height to cube two
	AddSequential(new SLtoRCCommand(Height::CUBEX2));

	// move robot from robot center to pyramid two
	// open gripper
	AddParallel(new RCtoPY2Command());
	AddSequential(new ToggleGripper(Action::OPEN));
		    
	// close gripper
	// intake the cube
	AddParallel(new ToggleGripper(Action::CLOSE));
	AddSequential(new ToggleIntake (Cube::TAKEIN));

	// move robot back to robot center
	// set elevator height to switch
	AddSequential(new PY2toRCCommand(Height::SWITCH));

	// move robot from robot center to switch left
	// eject the cube
	AddSequential(new RCtoSLCommand());
	AddSequential(new ToggleIntake(Cube::EJECT));
}
