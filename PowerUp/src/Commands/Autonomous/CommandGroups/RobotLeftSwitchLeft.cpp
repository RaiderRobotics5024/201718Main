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

	AddSequential(new DriveWithEncoders(168.00, 1.0, Height::NONE, 5.0));
	AddSequential(new RotateWithGyro   ( 90.00     ));
	AddSequential(new DriveWithEncoders( 21.06, 1.0, Height::NONE, 5.0));
	AddSequential(new ToggleIntake     (Cube::EJECT));
}
