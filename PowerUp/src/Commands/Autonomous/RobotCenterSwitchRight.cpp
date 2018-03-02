#include "Commands/Autonomous/RobotCenterSwitchRight.h"
#include "../../Utilities/Log.h"
#include "../DriveWithEncoders.h"

/**
 *
 */
RobotCenterSwitchRight::RobotCenterSwitchRight()
{
	LOG("[RobotCenterSwitchRight] Constructed");

	AddSequential(new DriveWithEncoders(132.0, 1.0));
}
