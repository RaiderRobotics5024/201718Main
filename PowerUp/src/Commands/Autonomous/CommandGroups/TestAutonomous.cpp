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

	// DRIVE A BOX PATTERN
	AddSequential(new ResetEncodersWithPause(  0.50));
	AddSequential(new TankDriveWithEncoders (30.00));
	AddSequential(new ResetEncodersWithPause(  0.50));
	AddSequential(new StaticTurn            (-45.00));
	AddSequential(new ResetEncodersWithPause(  0.50));
	AddSequential(new TankDriveWithEncoders (60.00));
	AddSequential(new ResetEncodersWithPause(  0.50));
	AddSequential(new StaticTurn            (45.00));
	AddSequential(new ResetEncodersWithPause(  0.50));
	AddSequential(new TankDriveWithEncoders (15.00));
	AddSequential(new ResetEncodersWithPause(  0.50));
	AddSequential(new ToggleIntake(0.6));
// If we go for 2 cubes
	AddSequential(new StaticTurn(130));
	AddSequential(new ResetEncodersWithPause(  0.5));
	AddSequential(new TankDriveWithEncoders(60));
	AddSequential(new StaticTurn(-130));
	AddParallel(new MoveElevator  (Height::BOTTOM));
	AddParallel(new ToggleGripper (Action::OPEN));
//	AddSequential(new TankDriveWithEncoders(20));
//	AddSequential(new TankDriveWithEncoders(20));
//	AddSequential(new ToggleIntake(-0.5));
//	AddSequential(new ResetEncodersWithPause(0.5));
////	AddParallel(new ToggleGripper(0.5));
//	AddSequential(new TankDriveWithEncoders(-40));
//	AddSequential(new StaticTurn(-45));
//	AddSequential(new TankDriveWithEncoders(40));
//	AddSequential(new ToggleIntake(0.5));



	//	AddSequential(new StaticTurn            (-90.00));
//	AddSequential(new TankDriveWithEncoders (100.00));
//	AddSequential(new ResetEncodersWithPause(  0.50));
//	AddSequential(new StaticTurn            (-90.00));
}
