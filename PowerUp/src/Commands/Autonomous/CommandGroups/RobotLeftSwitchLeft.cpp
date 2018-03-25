#include "RobotLeftSwitchLeft.h"
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
RobotLeftSwitchLeft::RobotLeftSwitchLeft()
{
	LOG("[RobotLeftSwitchLeft] Constructed");

	// Start the elevator service. This handles calls from the other
	// commands to move the elevator.  It runs throughout autonomous mode
	AddParallel(new ElevatorService());

	// FIRST CUBE
	AddSequential(new TankDriveWithEncoders (150.00, SWITCH, 5.0));
	AddSequential(new ResetEncodersWithPause(  0.50));
	AddSequential(new StaticTurn            ( 90.00));
	AddSequential(new ResetEncodersWithPause(  0.50));
	AddSequential(new TankDriveWithEncoders ( 21.06, NONE, 2.0));
	AddSequential(new ToggleIntake          (  1.00));

	// FIRST CUBE
//	AddSequential(new DriveWithEncoders(168.00, 1.0));
//	AddSequential(new RotateWithGyro   ( 90.00     ));
//	AddSequential(new DriveWithEncoders( 21.06, 1.0));
//	AddSequential(new ToggleIntake     ( -1.00     ));
}
