#include "TestAutonomous.h"
#include "../../../Utilities/Log.h"
#include "../../../RobotMap.h"
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
TestAutonomous::TestAutonomous()
{
	LOG("[TestAutonomous] Constructed");

	// LEFT/LEFT CUBE
//	AddParallel(new TankDriveWithEncoders (160.00));
//	AddParallel(new MoveElevator  (Height::SWITCH));
//
//	AddSequential(new ResetEncodersWithPause(  0.50));
//	AddSequential(new StaticTurn            ( 90.00));
//	AddSequential(new ResetEncodersWithPause(  0.50));
//
//	AddSequential(new TankDriveWithEncoders ( 21.06));
//	AddSequential(new ResetEncodersWithPause(  0.50));

	AddSequential(new ToggleIntake          ( 1.00));


	// LEFT/LEFT CUBE
//	AddParallel  (new DriveWithEncoders   (160.00));
//	AddParallel  (new MoveElevator(Height::SWITCH));
//	AddSequential(new RotateWithGyro      ( 90.00));
//	AddSequential(new DriveWithEncoders   ( 21.06));
//	AddSequential(new ToggleIntake        ( -1.00));
}
