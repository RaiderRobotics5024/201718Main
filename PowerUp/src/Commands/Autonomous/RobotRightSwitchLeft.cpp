#include "Commands/Autonomous/RobotRightSwitchLeft.h"
#include "../../Utilities/Log.h"
#include "../DriveWithEncoders.h"
#include "../DriveWithEncoders.h"
#include "../RotateWithGyro.h"

/**
 *
 */
RobotRightSwitchLeft::RobotRightSwitchLeft()
{
	LOG("[RobotRightSwitchLeft] Constructed");

	// 19.75 * pi / 4 = 15.51
	AddSequential(new DriveWithEncoders(120.0, -0.5));
//	AddSequential(new RotateWithGyro   (-90.0f      ));
//	AddSequential(new DriveWithEncoders( 15.51, -0.5));
//	AddSequential(new DriveWithEncoders(180.0 ,   1.0));
//	AddSequential(new RotateWithGyro   (90.0f       ));
//	AddSequential(new DriveWithEncoders( 15.51,  0.5));
//	AddSequential(new DriveWithEncoders( 24.0 ,  0.5));
}
