#include "Commands/Autonomous/RobotCenterSwitchRight.h"
#include "../../Utilities/Log.h"
#include "../DriveByPosition.h"

/**
 *
 */

RobotCenterSwitchRight::RobotCenterSwitchRight()
{
	LOG("[RobotCenterSwitchRight] Constructed");

	AddSequential(new DriveByPosition(60.0, 1.0));
}
