#include "Commands/Autonomous/RobotCenterSwitchRight.h"
#include "../../Utilities/Log.h"
#include "../../RobotMap.h"
#include "../DriveWithEncoders.h"
#include "../StaticTurn.h"
#include "../EjectCube.h"

/**
 *
 */
RobotCenterSwitchRight::RobotCenterSwitchRight()
{
	LOG("[RobotCenterSwitchRight] Constructed");

	AddSequential(new DriveWithEncoders(110.0, -0.5));

//	AddSequential(new DriveWithEncoders( 25.0, -1.0));
//	AddSequential(new StaticTurn       ( 20.0      ));
//	AddSequential(new DriveWithEncoders( 50.0, -1.0));
//	AddSequential(new StaticTurn       (-20.0      ));
//	AddSequential(new DriveWithEncoders( 25.0, -1.0));
//	AddSequential(new EjectCube        (  1.0      ));

	//	AddSequential(new StaticTurn       ( 90.0      ));
//	AddSequential(new DriveWithEncoders( 40.0, -0.5));
//	AddSequential(new StaticTurn       (-90.0      ));
//	AddSequential(new DriveWithEncoders( 60.0, -0.5));
//	AddSequential(new EjectCube        (  1.0      ));
}
