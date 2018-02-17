#include "Commands/Autonomous/RobotRightSwitchRight.h"
#include "../../Utilities/Log.h"
#include "../DriveByPosition.h"
#include "../RotateByPosition.h"
#include "../RotateToAngle.h"

/**
 *
 */

RobotRightSwitchRight::RobotRightSwitchRight()
{
	LOG("[RobotRightSwitchRight] Constructed");

	AddSequential(new DriveByPosition(60.0, 1.0));
//	AddSequential(new RotateToAngle(-90.0f));
	AddSequential(new RotateByPosition(15.51, -0.5));
	AddSequential(new DriveByPosition(24.0, 0.5));
}
