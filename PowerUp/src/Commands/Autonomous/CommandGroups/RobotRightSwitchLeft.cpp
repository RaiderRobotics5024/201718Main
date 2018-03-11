#include "RobotRightSwitchLeft.h"
#include "../../../Utilities/Log.h"
#include "../DriveWithEncoders.h"
#include "../RotateWithGyro.h"
#include "../ToggleIntake.h"

/**
 *
 */
RobotRightSwitchLeft::RobotRightSwitchLeft()
{
	LOG("[RobotRightSwitchLeft] Constructed");

	AddSequential(new DriveWithEncoders(228.74, 1.0));
	AddSequential(new RotateWithGyro   (-90.00     ));
	AddSequential(new DriveWithEncoders(168.94, 1.0));
	AddSequential(new RotateWithGyro   (-90.00     ));
	AddSequential(new DriveWithEncoders( 13.74, 1.0));
	AddSequential(new ToggleIntake     ( -1.00     ));
}
