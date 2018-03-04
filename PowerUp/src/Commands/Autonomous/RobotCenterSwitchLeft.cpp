#include "Commands/Autonomous/RobotCenterSwitchLeft.h"
#include "../../Utilities/Log.h"
#include "../../RobotMap.h"
#include "../DriveWithEncoders.h"
#include "../RotateWithEncoders.h"
#include "../RotateWithGyro.h"
#include "../StaticTurn.h"
#include "../EjectCube.h"

/**
 *
 */
RobotCenterSwitchLeft::RobotCenterSwitchLeft()
{
	LOG("[RobotCenterSwitchLeft] Constructed");

	AddSequential(new DriveWithEncoders( 35.00, -1.0));
	AddSequential(new RotateWithGyro   (-45.00      ));
	AddSequential(new DriveWithEncoders( 80.00, -1.0));
	AddSequential(new RotateWithGyro   ( 45.00      ));
	AddSequential(new DriveWithEncoders( 40.00, -1.0));
	AddSequential(new EjectCube        ( -1.00      ));
}
