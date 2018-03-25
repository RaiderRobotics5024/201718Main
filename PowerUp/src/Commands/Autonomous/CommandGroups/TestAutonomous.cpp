#include "TestAutonomous.h"
#include "../../../Utilities/Log.h"
#include "../../../RobotMap.h"
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
TestAutonomous::TestAutonomous()
{
	LOG("[TestAutonomous] Constructed");

	AddParallel  (new ElevatorService());
	AddSequential(new TankDriveWithEncoders(100.00, 3.0));

	// LEFT/LEFT CUBE
//
//	AddSequential(new ResetEncodersWithPause(  0.50));
//	AddSequential(new StaticTurn            ( 90.00));
//	AddSequential(new ResetEncodersWithPause(  0.50));
//
//	AddSequential(new TankDriveWithEncoders ( 21.06));
//	AddSequential(new ResetEncodersWithPause(  0.50));

//	AddSequential(new ToggleIntake          ( 1.00));


	// LEFT/LEFT CUBE
//	AddParallel  (new DriveWithEncoders   (160.00));
//	AddParallel  (new MoveElevator(Height::SWITCH));
//	AddSequential(new RotateWithGyro      ( 90.00));
//	AddSequential(new DriveWithEncoders   ( 21.06));
//	AddSequential(new ToggleIntake        ( -1.00));
}
