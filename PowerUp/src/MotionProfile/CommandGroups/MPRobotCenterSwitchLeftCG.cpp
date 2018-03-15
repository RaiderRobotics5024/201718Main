#include "MPRobotCenterSwitchLeftCG.h"
#include "../Commands/RCtoSLCommand.h"
#include "../Commands/SLtoRCCommand.h"
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
MPRobotCenterSwitchLeftCG::MPRobotCenterSwitchLeftCG()
{
	// FIRST CUBE
	// move from robot center to switch left
	// eject the cube
	AddSequential(new RCtoSLCommand());
	AddSequential(new ToggleIntake(-1.00));

	// SECOND CUBE
	// move from switch left back to robot center
	// set elevator height to cube one
	AddParallel(new SLtoRCCommand());
	AddSequential(new MoveElevator(Height::CUBE));

	// move robot to pyramid 1 position
	// open the gripper
	AddParallel(new RCtoPY1Command());
	AddSequential(new ToggleGripper(Action::OPEN));
	
	// close the gripper
	// intake the cube
	AddParallel(new ToggleGripper(Action::CLOSE));
	AddSequential(new ToggleIntake ( 1.00));

	// move robot back to robot center
	// set elevator height to switch
	AddParallel(new PY1toRCCommand());
	AddSequential(new MoveElevator(Height::SWITCH));

	// move robot from robot center to switch left
	// eject the cube
	AddSequential(new RCtoSLCommand());
	AddSequential(new ToggleIntake(-1.00));

	// THIRD CUBE
	// move robot from switch left back to robot center
	// set elevator height to cube two
	AddParallel(new SLtoRCCommand());
	AddSequential(new MoveElevator(Height::CUBEX2));

	// move robot from robot center to pyramid two
	// open gripper
	AddParallel(new RCtoPY2Command());
	AddSequential(new ToggleGripper(Action::OPEN));
		    
	// close gripper
	// intake the cube
	AddParallel(new ToggleGripper(Action::CLOSE));
	AddSequential(new ToggleIntake (1.00));

	// move robot back to robot center
	// set elevator height to switch
	AddParallel(new PY2toRCCommand());
	AddSequential(new MoveElevator(Height::SWITCH));

	// move robot from robot center to switch left
	// eject the cube
	AddSequential(new RCtoSLCommand());
	AddSequential(new ToggleIntake(-1.00));
}
