#include "Commands/Autonomous/RobotLeftSwitchLeft.h"
#include "../../Utilities/Log.h"
#include "../DriveWithEncoders.h"
#include "../RotateWithEncoders.h"
#include "../RotateWithGyro.h"

/**
 *
 */
RobotLeftSwitchLeft::RobotLeftSwitchLeft()
{
	LOG("[RobotLeftSwitchLeft] Constructed");

	AddSequential(new DriveWithEncoders (60.0 , 1.0));
//	AddSequential(new RotateWithGyro    (90.0f     ));
	AddSequential(new RotateWithEncoders(15.51, 0.5));
	AddSequential(new DriveWithEncoders (24.0 , 0.5));
}
