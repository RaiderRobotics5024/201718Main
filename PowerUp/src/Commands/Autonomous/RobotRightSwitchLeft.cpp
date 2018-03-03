#include "Commands/Autonomous/RobotRightSwitchLeft.h"
#include "../../Utilities/Log.h"
#include "../../RobotMap.h"
#include "../DriveWithEncoders.h"
#include "../DriveWithEncoders.h"
#include "../RotateWithGyro.h"
#include "../StaticTurn.h"
#include "../EjectCube.h"

/**
 *
 */
RobotRightSwitchLeft::RobotRightSwitchLeft()
{
	LOG("[RobotRightSwitchLeft] Constructed");

	AddSequential(new DriveWithEncoders(110.0, -0.5));
//	AddSequential(new StaticTurn       (-90.0      ));
//	AddSequential(new DriveWithEncoders(120.0, -0.5));
//	AddSequential(new StaticTurn       ( 90.0      ));
//	AddSequential(new DriveWithEncoders( 60.0, -0.5));
//	AddSequential(new EjectCube        (  1.0      ));

	//	AddSequential(new RotateWithGyro   (-90.0f      ));
//	AddSequential(new DriveWithEncoders( 15.51, -0.5));
//	AddSequential(new DriveWithEncoders(180.0 ,   1.0));
//	AddSequential(new RotateWithGyro   (90.0f       ));
//	AddSequential(new DriveWithEncoders( 15.51,  0.5));
//	AddSequential(new DriveWithEncoders( 24.0 ,  0.5));
}
