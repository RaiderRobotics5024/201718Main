#include "Commands/Autonomous/RobotCenterSwitchLeft.h"
#include "../../Utilities/Log.h"
#include "DriveWithEncoders.h"
#include "RotateWithGyro.h"
#include "ToggleIntake.h"

/**
 *
 */
RobotCenterSwitchLeft::RobotCenterSwitchLeft()
{
	LOG("[RobotCenterSwitchLeft] Constructed");

	AddSequential(new DriveWithEncoders( 19.00, 1.0));
	AddSequential(new RotateWithGyro   (-41.15     ));
	AddSequential(new DriveWithEncoders( 85.00, 1.0));
	AddSequential(new RotateWithGyro   ( 41.15     ));
	AddSequential(new DriveWithEncoders( 19.00, 1.0));
	AddSequential(new ToggleIntake     ( -1.00     ));
}
