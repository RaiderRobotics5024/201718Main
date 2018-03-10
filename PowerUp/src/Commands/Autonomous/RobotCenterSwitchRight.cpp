#include "Commands/Autonomous/RobotCenterSwitchRight.h"
#include "../../Utilities/Log.h"
#include "DriveWithEncoders.h"
#include "RotateWithGyro.h"
#include "ToggleIntake.h"

/**
 *
 */
RobotCenterSwitchRight::RobotCenterSwitchRight()
{
	LOG("[RobotCenterSwitchRight] Constructed");

	AddSequential(new DriveWithEncoders( 19.00, 1.0));
	AddSequential(new RotateWithGyro   ( 37.41     ));
	AddSequential(new DriveWithEncoders( 80.57, 1.0));
	AddSequential(new RotateWithGyro   (-37.41     ));
	AddSequential(new DriveWithEncoders( 19.00, 1.0));
	AddSequential(new ToggleIntake     ( -1.00     ));
}
