#include "RobotRightSwitchRight.h"
#include "../../../Utilities/Log.h"
#include "../DriveWithEncoders.h"
#include "../RotateWithGyro.h"
#include "../ToggleIntake.h"

/**
 *
 */
RobotRightSwitchRight::RobotRightSwitchRight()
{
	LOG("[RobotRightSwitchRight] Constructed");

	AddSequential(new DriveWithEncoders(168.00, 1.0));
	AddSequential(new RotateWithGyro   (-90.00     ));
	AddSequential(new DriveWithEncoders( 21.06, 1.0));
	AddSequential(new ToggleIntake     ( -1.00     ));
}
