#include "TestAutonomous.h"
#include "../../Utilities/Log.h"
#include "../../RobotMap.h"
#include "../DriveWithEncoders.h"
#include "../RotateWithEncoders.h"
#include "../RotateWithGyro.h"
#include "../StaticTurn.h"
#include "../EjectCube.h"
#include "../OpenCloseGripper.h"
#include "../MoveElevator.h"

/**
 *
 */
TestAutonomous::TestAutonomous()
{
	LOG("[TestAutonomous] Constructed");
	
	// -- START 2 CUBE AUTO -- (Robot center, Switch right)
	AddSequential(new DriveWithEncoders( 70.00 - HALF_ROBOT_LENGTH, -1.0));
	AddSequential(new RotateWithGyro   ( 90.00      ));
	AddSequential(new DriveWithEncoders( 70.00 + HALF_ROBOT_LENGTH + 2, -1.0));
	AddSequential(new RotateWithGyro   (-90.00      ));
	AddSequential(new DriveWithEncoders( 56/2, -1.0 ));
	AddSequential(new RotateWithGyro   (-45.00      ));
	AddSequential(new EjectCube        ( -1.00      ));
	AddSequential(new RotateWithGyro   ( 45.00      ));
	AddSequential(new DriveWithEncoders( 56/2 + HALF_ROBOT_LENGTH, -1.0));
	AddSequential(new MoveElevator     (0           ));
	AddSequential(new RotateWithGyro   (-90.00      ));
	AddSequential(new DriveWithEncoders( 2.00, -1.0 ));
	AddSequential(new RotateWithGyro   (-20.00      ));
	AddSequential(new OpenCloseGripper (-1          ));
	AddSequential(new DriveWithEncoders( 40.00, -1.0));
	AddSequential(new EjectCube        ( 1.00       ));
	AddSequential(new OpenCloseGripper (1           ));
	AddSequential(new MoveElevator     (1           ));
	AddSequential(new DriveWithEncoders(-20.00, -1.0));
	AddSequential(new RotateWithGyro   (-20.00      ));
	AddSequential(new DriveWithEncoders( 10.00, -1.0));
	AddSequential(new EjectCube        ( 1.00       ));
	// -- END 2 CUBE AUTO --
	
	// AddSequential(new DriveWithEncoders( 40.00 - HALF_ROBOT_LENGTH, -1.0));
	// AddSequential(new RotateWithGyro   (-20.00      ));
	// AddSequential(new DriveWithEncoders( 60.00, -1.0));
	// AddSequential(new RotateWithGyro   ( 20.00      ));
	// AddSequential(new DriveWithEncoders( 40.00, -1.0));
	// AddSequential(new EjectCube        ( -1.00      ));

//	AddSequential(new DriveWithEncoders ( 40.00, -1.0)); // drive one rotation
//	AddSequential(new RotateWithEncoders( 15.51, -1.0)); // turn 90 degrees
//	AddSequential(new RotateWithGyro    (-90.0f      ));
//	AddSequential(new DriveWithEncoders ( 40.00, -1.0)); // drive one rotation
//	AddSequential(new RotateWithGyro    (-90.0f      ));
//	AddSequential(new DriveWithEncoders ( 40.00, -1.0)); // drive one rotation
//	AddSequential(new RotateWithEncoders(-15.51, -1.0)); // turn -90 degrees
//	AddSequential(new DriveWithEncoders ( 18.85, -1.0)); // drive one rotation
}

