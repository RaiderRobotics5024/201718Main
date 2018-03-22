#include "RobotCenterSwitchLeft.h"
#include "../../../Utilities/Log.h"
#include "../DriveWithEncoders.h"
#include "../ResetEncodersWithPause.h"
#include "../RotateWithGyro.h"
#include "../MoveElevator.h"
#include "../ToggleGripper.h"
#include "../ToggleIntake.h"
#include "../TankDriveWithEncoders.h"
#include "../../StaticTurn.h"

/**
 *
 */
RobotCenterSwitchLeft::RobotCenterSwitchLeft()
{
	LOG("[RobotCenterSwitchLeft] Constructed");

	// FIRST CUBE
	AddSequential(new TankDriveWithEncoders ( 19.00));
	AddSequential(new ResetEncodersWithPause(  0.50));
	AddSequential(new StaticTurn            (-41.15));
	AddSequential(new TankDriveWithEncoders ( 85.00));
	AddSequential(new ResetEncodersWithPause(  0.50));
	AddSequential(new StaticTurn            ( 41.15));
	AddSequential(new TankDriveWithEncoders ( 19.00));
	AddSequential(new ResetEncodersWithPause(  0.50));
	AddSequential(new MoveElevator  (Height::SWITCH));
	AddSequential(new ToggleIntake          ( -1.00));

	// FIRST CUBE
//	AddSequential(new DriveWithEncoders( 19.00, 1.0));
//	AddSequential(new RotateWithGyro   (-41.15     ));
//	AddSequential(new DriveWithEncoders( 85.00, 1.0));
//	AddSequential(new RotateWithGyro   ( 41.15     ));
//	AddParallel  (new DriveWithEncoders( 19.00, 1.0));
//	AddSequential(new MoveElevator(Height::SWITCH));
//	AddSequential(new ToggleIntake     ( -1.00     ));

	//SECOND CUBE
/*
	AddParallel  (new DriveWithEncoders(-48.00, 1.0));
	AddSequential(new MoveElevator(Height::BOTTOM));

	AddParallel  (new RotateWithGyro   ( 90.00     ));
	AddSequential(new ToggleGripper    ( Action::OPEN));

	AddSequential(new DriveWithEncoders( 52.44, 1.0));
	AddSequential(new RotateWithGyro   (-90.00     ));
	AddSequential(new DriveWithEncoders(  6.00, 1.0));

	AddParallel  (new ToggleGripper    (Action::CLOSE));
	AddSequential(new ToggleIntake     (  1.00     ));

	AddSequential(new DriveWithEncoders( -6.00, 1.0));
	AddSequential(new RotateWithGyro   (-90.00     ));
	AddSequential(new DriveWithEncoders( 52.44, 1.0));
	AddSequential(new RotateWithGyro   ( 90.00     ));
	AddParallel  (new DriveWithEncoders( 48.00, 1.0));
	AddSequential(new MoveElevator(Height::SWITCH));

	AddSequential(new ToggleIntake     ( -1.00     ));
*/
}
