#include "Commands/Autonomous/RobotCenterSwitchRight.h"
#include "../../Utilities/Log.h"
#include "../../RobotMap.h"
#include "../DriveWithEncoders.h"
#include "../RotateWithGyro.h"
#include "../StaticTurn.h"
#include "../EjectCube.h"

/**
 *
 */
RobotCenterSwitchRight::RobotCenterSwitchRight()
{
	LOG("[RobotCenterSwitchRight] Constructed");

	AddSequential(new DriveWithEncoders( 35.00, -1.0));
	AddSequential(new RotateWithGyro   ( 45.00      ));
	AddSequential(new DriveWithEncoders( 75.00, -1.0));
	AddSequential(new RotateWithGyro   (-45.00      ));
	AddSequential(new DriveWithEncoders( 40.00, -1.0));
	AddSequential(new EjectCube        ( -1.00      ));
}
