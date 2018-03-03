#include "Commands/Autonomous/RobotLeftSwitchRight.h"
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
RobotLeftSwitchRight::RobotLeftSwitchRight()
{
	LOG("[RobotLeftSwitchRight] Constructed");

	AddSequential(new DriveWithEncoders(110.0, -0.5));
//	AddSequential(new StaticTurn       ( 90.0      ));
//	AddSequential(new DriveWithEncoders(120.0, -0.5));
//	AddSequential(new StaticTurn       (-90.0      ));
//	AddSequential(new DriveWithEncoders( 60.0, -0.5));
//	AddSequential(new EjectCube        (  1.0      ));

	//	AddSequential(new StaticTurn(90.0));
//	AddSequential(new RotateWithGyro( 90.0f     ));
//	AddSequential(new RotateWithEncoders( 15.51, 0.5));
//	AddSequential(new DriveWithEncoders (180.0 , 1.0));
//	AddSequential(new RotateWithGyro( 90.0f     ));
//	AddSequential(new StaticTurn(90.0));
//	AddSequential(new RotateWithEncoders( 15.51, 0.5));
//	AddSequential(new DriveWithEncoders ( 24.0 , 0.5));
}
