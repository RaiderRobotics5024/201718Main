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

	AddSequential(new DriveWithEncoders(110.0, -0.5));

//	AddSequential(new DriveWithEncoders( 25.0, -1.0));
//	AddSequential(new StaticTurn       (-20.0      ));
//	AddSequential(new DriveWithEncoders( 50.0, -1.0));
//	AddSequential(new StaticTurn       ( 20.0      ));
//	AddSequential(new DriveWithEncoders( 25.0, -1.0));
//	AddSequential(new EjectCube        (  1.0      ));

//	AddSequential(new RotateWithGyro    (-90.0f      ));
//	AddSequential(new RotateWithEncoders( 15.51, -0.5));
//	AddSequential(new DriveWithEncoders (120.0 ,  1.0));
//	AddSequential(new RotateWithGyro    ( 90.0f      ));
//	AddSequential(new RotateWithEncoders( 15.51,  0.5));
//	AddSequential(new DriveWithEncoders ( 60.0 ,  0.8));
}
