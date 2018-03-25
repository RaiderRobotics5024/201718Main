#include "RobotRightSwitchRight.h"
#include "../../../Utilities/Log.h"
#include "../DriveWithEncoders.h"
#include "../ElevatorService.h"
#include "../ResetEncodersWithPause.h"
#include "../RotateWithGyro.h"
#include "../ToggleGripper.h"
#include "../ToggleIntake.h"
#include "../TankDriveWithEncoders.h"
#include "../../StaticTurn.h"

/**
 *
 */
RobotRightSwitchRight::RobotRightSwitchRight()
{
	LOG("[RobotRightSwitchRight] Constructed");

	// FIRST CUBE
	AddSequential(new TankDriveWithEncoders (150.00, 5.0));
	AddSequential(new ResetEncodersWithPause(  0.50));
	AddSequential(new StaticTurn            (-90.00));
	AddSequential(new ResetEncodersWithPause(  0.50));
	AddSequential(new TankDriveWithEncoders ( 21.06, 2.0));
	AddSequential(new ToggleIntake          (  1.00));

	// FIRST CUBE
//	AddSequential(new DriveWithEncoders(168.00, 1.0));
//	AddSequential(new RotateWithGyro   (-90.00     ));
//	AddSequential(new DriveWithEncoders( 21.06, 1.0));
//	AddSequential(new ToggleIntake     ( -1.00     ));
}
