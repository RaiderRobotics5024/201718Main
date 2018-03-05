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
#include "../IntakeDriveWithEncoders.h"

RobotCenterSwitchRight::RobotCenterSwitchRight()
{
	LOG("[RobotCenterSwitchRight] Constructed");
	
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
	
	// THIS IS VERY EXPERIMENTAL
	AddSequential(new IntakeDriveWithEncoders (40.00, -1.0, 1.00);
	
	/*	ADD THIS BACK IF ABOVE CODE WON'T WORK
	AddSequential(new DriveWithEncoders( 40.00, -1.0));
	AddSequential(new EjectCube        ( 1.00       ));
	*/
	AddSequential(new OpenCloseGripper (1           ));
	AddSequential(new MoveElevator     (1           ));
	AddSequential(new DriveWithEncoders(-20.00, -1.0));
	AddSequential(new RotateWithGyro   (-20.00      ));
	AddSequential(new DriveWithEncoders( 10.00, -1.0));
	AddSequential(new EjectCube        ( 1.00       ));
	// -- END 2 CUBE AUTO --
}

