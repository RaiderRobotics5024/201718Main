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
	// FIRST CUBE
	// move from robot center to switch left
	// eject the cube
	AddSequential(new RCtoSLCommand());
	AddSequential(new ToggleIntake(-1.00));

	// SECOND CUBE
	// move from switch left back to robot center
	// set elevator height to cube one
	AddParallel(new SLtoRCCommand());
	AddSequential(new MoveElevator(Elevator::Positions::CUBE));

	// move robot to pyramid 1 position
	// open the gripper
	AddParallel(new RCtoPY1Command());
	AddSequential(new ToggleGripper(-1.00));
	
	// close the gripper
	// intake the cube
	AddParallel(new ToggleGripper(1.00));
	AddSequential(new ToggleIntake ( 1.00));

	// move robot back to robot center
	// set elevator height to switch
	AddParallel(new PY1toRCCommand());
	AddSequential(new MoveElevator(Elevator::Positions::SWITCH));

	// move robot from robot center to switch left
	// eject the cube
	AddSequential(new RCtoSLCommand());
	AddSequential(new ToggleIntake(-1.00));

	// THIRD CUBE
	// move robot from switch left back to robot center
	// set elevator height to cube two
	AddParallel(new SLtoRCCommand());
	AddSequential(new MoveElevator(Elevator::Positions::CUBEX2));

	// move robot from robot center to pyramid two
	// open gripper
	AddParallel(new RCtoPY2Command());
	AddSequential(new ToggleGripper(-1.00));
		    
	// close gripper
	// intake the cube
	AddParallel(new ToggleGripper(1.00));
	AddSequential(new ToggleIntake (1.00));

	// move robot back to robot center
	// set elevator height to switch
	AddParallel(new PY2toRCCommand());
	AddSequential(new MoveElevator(Elevator::Positions::SWITCH));

	// move robot from robot center to switch left
	// eject the cube
	AddSequential(new RCtoSLCommand());
	AddSequential(new ToggleIntake(-1.00));
}
