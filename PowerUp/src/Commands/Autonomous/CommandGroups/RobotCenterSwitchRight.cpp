#include "RobotCenterSwitchRight.h"
#include "../../../Utilities/Log.h"
#include "../DriveWithEncoders.h"
#include "../RotateWithGyro.h"
#include "../MoveElevator.h"
#include "../ToggleIntake.h"
#include "../ToggleGripper.h"

/**
 *
 */
RobotCenterSwitchRight::RobotCenterSwitchRight()
{
	LOG("[RobotCenterSwitchRight] Constructed");

	// First cube
	AddSequential(new DriveWithEncoders( 19.00, 1.0));
	AddSequential(new RotateWithGyro   ( 37.41     ));
	AddSequential(new DriveWithEncoders( 80.57, 1.0));
	AddSequential(new RotateWithGyro   (-37.41     ));
	AddParallel  (new DriveWithEncoders( 19.00, 1.0));
//	AddSequential(new MoveElevator(Height::SWITCH));
	AddSequential(new ToggleIntake     ( -1.00     ));

	// Second cube
	AddParallel  (new DriveWithEncoders(-48.00, 1.0));
//	AddSequential(new MoveElevator(Height::BOTTOM));

	AddParallel  (new RotateWithGyro   (-90.00     ));
	AddSequential(new ToggleGripper    (Action::OPEN));

	AddSequential(new DriveWithEncoders( 52.44, 1.0));
	AddSequential(new RotateWithGyro   ( 90.00     ));
	AddSequential(new DriveWithEncoders(  6.00, 1.0));

	AddParallel  (new ToggleGripper    (Action::CLOSE));
	AddSequential(new ToggleIntake     (  1.00     ));

	AddSequential(new DriveWithEncoders( -6.00, 1.0));
	AddSequential(new RotateWithGyro   ( 90.00     ));
	AddSequential(new DriveWithEncoders( 52.44, 1.0));
	AddSequential(new RotateWithGyro   (-90.00     ));
	AddParallel  (new DriveWithEncoders( 48.00, 1.0));
//	AddSequential(new MoveElevator(Height::SWITCH));

	AddSequential(new ToggleIntake     ( -1.00     ));
}
