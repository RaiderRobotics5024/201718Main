#include "Commands/Autonomous/RobotRightSwitchRight.h"
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
RobotRightSwitchRight::RobotRightSwitchRight()
{
	LOG("[RobotRightSwitchRight] Constructed");

	AddSequential(new DriveWithEncoders (110.0 , -0.5));
//	AddSequential(new RotateWithEncoders( 15.51, -1.0));
//	AddSequential(new DriveWithEncoders ( 10.0 , -1.0));
//	AddSequential(new EjectCube         (  1.0       ));

//	AddSequential(new StaticTurn       (-90.0      ));
//	AddSequential(new RotateWithGyro    (-90.0f      ));
//	AddSequential(new DriveWithEncoders ( 48.0 ,  0.5));
}
