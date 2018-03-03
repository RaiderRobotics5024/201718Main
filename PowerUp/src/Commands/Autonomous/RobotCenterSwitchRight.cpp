#include "Commands/Autonomous/RobotCenterSwitchRight.h"
#include "../../Utilities/Log.h"
#include "../DriveWithEncoders.h"
#include "../StaticTurn.h"
#include "../EjectCube.h"

/**
 *
 */
RobotCenterSwitchRight::RobotCenterSwitchRight()
{
	LOG("[RobotCenterSwitchRight] Constructed");

	AddSequential(new DriveWithEncoders(120.0, -0.5));
//	AddSequential(new StaticTurn       ( 90.0      ));
//	AddSequential(new EjectCube        (  1.0      ));
}
