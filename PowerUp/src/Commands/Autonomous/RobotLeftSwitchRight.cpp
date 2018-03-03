#include "Commands/Autonomous/RobotLeftSwitchRight.h"
#include "../../Utilities/Log.h"
#include "../DriveWithEncoders.h"
#include "../RotateWithEncoders.h"
#include "../RotateWithGyro.h"
#include "../StaticTurn.h"

/**
 *
 */
RobotLeftSwitchRight::RobotLeftSwitchRight()
{
	LOG("[RobotLeftSwitchRight] Constructed");

	// 19.75 * pi / 4 = 15.51
	AddSequential(new DriveWithEncoders(120.0, -0.5));
//	AddSequential(new StaticTurn(90.0));
//	AddSequential(new RotateWithGyro( 90.0f     ));
//	AddSequential(new RotateWithEncoders( 15.51, 0.5));
//	AddSequential(new DriveWithEncoders (180.0 , 1.0));
//	AddSequential(new RotateWithGyro( 90.0f     ));
//	AddSequential(new StaticTurn(90.0));
//	AddSequential(new RotateWithEncoders( 15.51, 0.5));
//	AddSequential(new DriveWithEncoders ( 24.0 , 0.5));
}
