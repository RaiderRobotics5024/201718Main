#include "RobotLeftSwitchRight.h"
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

RobotLeftSwitchRight::RobotLeftSwitchRight()
{
	LOG("[RobotLeftSwitchRight] Constructed");

	// Start the elevator service
	AddParallel(new ElevatorService());

	// FIRST CUBE
	AddSequential(new TankDriveWithEncoders (220.74, 5.0));
	AddSequential(new ResetEncodersWithPause(  0.50));
	AddSequential(new StaticTurn            ( 90.00));
	AddSequential(new TankDriveWithEncoders (208.94, 3.0));
	AddSequential(new ResetEncodersWithPause(  0.50));
	AddSequential(new StaticTurn            ( 90.00));
	AddSequential(new ResetEncodersWithPause(  0.50));
	AddSequential(new TankDriveWithEncoders ( 13.74, 2.0));
	AddSequential(new ToggleIntake          (  1.00));

	// FIRST CUBE
//	AddSequential(new DriveWithEncoders(228.74, 1.0));
//	AddSequential(new RotateWithGyro   ( 90.00     ));
//	AddSequential(new DriveWithEncoders(168.94, 1.0));
//	AddSequential(new RotateWithGyro   ( 90.00     ));
//	AddSequential(new DriveWithEncoders( 13.74, 1.0));
//	AddSequential(new ToggleIntake     ( -1.00     ));
}
