#include "TestAutonomous.h"
#include "../../../Utilities/Log.h"
#include "../../../RobotMap.h"
#include "../DriveWithEncoders.h"
#include "../ElevatorService.h"
#include "../RotateWithEncoders.h"
#include "../RotateWithGyro.h"
#include "../ToggleIntake.h"

/**
 *
 */
TestAutonomous::TestAutonomous()
{
	LOG("[TestAutonomous] Constructed");

	// Start the elevator service. This handles calls from the other
	// commands to move the elevator.  It runs throughout autonomous mode
	AddParallel(new ElevatorService());

//	AddSequential(new DriveWithEncoders ( 40.00, -1.0)); // drive one rotation
//	AddSequential(new RotateWithEncoders( 15.51, -1.0)); // turn 90 degrees
//	AddSequential(new RotateWithGyro    (-90.0f      ));
//	AddSequential(new DriveWithEncoders ( 40.00, -1.0)); // drive one rotation
//	AddSequential(new RotateWithGyro    (-90.0f      ));
//	AddSequential(new DriveWithEncoders ( 40.00, -1.0)); // drive one rotation
//	AddSequential(new RotateWithEncoders(-15.51, -1.0)); // turn -90 degrees
//	AddSequential(new DriveWithEncoders ( 18.85, -1.0)); // drive one rotation
}
