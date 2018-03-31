#include "RobotRightSwitchRight.h"
#include "../../../Utilities/Log.h"
#include "../DriveWithEncoders.h"
#include "../ElevatorService.h"
#include "../RotateWithGyro.h"
#include "../ToggleIntake.h"

/**
 *
 */
RobotRightSwitchRight::RobotRightSwitchRight()
{
	LOG("[RobotRightSwitchRight] Constructed");

	// Start the elevator service. This handles calls from the other
	// commands to move the elevator.  It runs throughout autonomous mode
	AddParallel(new ElevatorService());

	AddSequential(new DriveWithEncoders(168.00, 1.0, Height::NONE, 5.0));
	AddSequential(new RotateWithGyro   (-90.00     ));
	AddSequential(new DriveWithEncoders( 21.06, 1.0, Height::NONE, 5.0));
	AddSequential(new ToggleIntake     (Cube::EJECT));
}
