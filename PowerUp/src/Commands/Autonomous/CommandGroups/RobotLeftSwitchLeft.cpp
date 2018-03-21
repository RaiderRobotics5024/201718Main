#include "RobotLeftSwitchLeft.h"
#include "../../../Utilities/Log.h"
#include "../DriveWithEncoders.h"
#include "../RotateWithGyro.h"
#include "../ToggleIntake.h"

/**
 *
 */
RobotLeftSwitchLeft::RobotLeftSwitchLeft()
{
	LOG("[RobotLeftSwitchLeft] Constructed");

	// FIRST CUBE
	AddSequential(new DriveWithEncoders(168.00, 1.0));
	AddSequential(new RotateWithGyro   ( 90.00     ));
	AddSequential(new DriveWithEncoders( 21.06, 1.0));
	AddSequential(new ToggleIntake     ( -1.00     ));
}
