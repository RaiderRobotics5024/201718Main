#include "TestAutonomous.h"
#include "../../Utilities/Log.h"
#include "../../RobotMap.h"
#include "DriveWithEncoders.h"
#include "RotateWithEncoders.h"
#include "RotateWithGyro.h"
#include "ToggleIntake.h"

/**
 *
 */
TestAutonomous::TestAutonomous()
{
	LOG("[TestAutonomous] Constructed");

	AddSequential(new DriveWithEncoders( 40.00 - HALF_ROBOT_LENGTH, -1.0));
	AddSequential(new RotateWithGyro   (-20.00      ));
	AddSequential(new DriveWithEncoders( 60.00, -1.0));
	AddSequential(new RotateWithGyro   ( 20.00      ));
	AddSequential(new DriveWithEncoders( 40.00, -1.0));
	AddSequential(new ToggleIntake     ( -1.00      ));

//	AddSequential(new DriveWithEncoders ( 40.00, -1.0)); // drive one rotation
//	AddSequential(new RotateWithEncoders( 15.51, -1.0)); // turn 90 degrees
//	AddSequential(new RotateWithGyro    (-90.0f      ));
//	AddSequential(new DriveWithEncoders ( 40.00, -1.0)); // drive one rotation
//	AddSequential(new RotateWithGyro    (-90.0f      ));
//	AddSequential(new DriveWithEncoders ( 40.00, -1.0)); // drive one rotation
//	AddSequential(new RotateWithEncoders(-15.51, -1.0)); // turn -90 degrees
//	AddSequential(new DriveWithEncoders ( 18.85, -1.0)); // drive one rotation
}
