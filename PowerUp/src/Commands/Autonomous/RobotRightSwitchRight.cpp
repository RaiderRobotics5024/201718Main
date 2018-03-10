#include "Commands/Autonomous/RobotRightSwitchRight.h"
#include "../../Utilities/Log.h"
#include "DriveWithEncoders.h"
#include "RotateWithEncoders.h"
#include "RotateWithGyro.h"

/**
 *
 */
RobotRightSwitchRight::RobotRightSwitchRight()
{
	LOG("[RobotRightSwitchRight] Constructed");

	AddSequential(new DriveWithEncoders ( 60.0 ,  1.0));
//	AddSequential(new RotateToAngle     (-90.0f      ));
	AddSequential(new RotateWithEncoders( 15.51, -0.5));
	AddSequential(new DriveWithEncoders ( 24.0 ,  0.5));
}
