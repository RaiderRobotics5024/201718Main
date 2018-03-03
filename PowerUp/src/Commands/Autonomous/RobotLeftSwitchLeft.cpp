#include "Commands/Autonomous/RobotLeftSwitchLeft.h"
#include "../../Utilities/Log.h"
#include "../DriveWithEncoders.h"
#include "../RotateWithEncoders.h"
#include "../RotateWithGyro.h"
#include "../StaticTurn.h"
#include "../EjectCube.h"

/**
 *
 */
RobotLeftSwitchLeft::RobotLeftSwitchLeft()
{
	LOG("[RobotLeftSwitchLeft] Constructed");

	AddSequential(new DriveWithEncoders(120.0, -0.5));
//	AddSequential(new StaticTurn(90.0));
//	AddSequential(new RotateWithGyro    ( 90.0f     ));
//	AddSequential(new RotateWithEncoders( 15.51, 0.5));
//	AddSequential(new DriveWithEncoders ( 48.0 , -0.5));
//	AddSequential(new EjectCube         (  1.0      ));
}
