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
//	AddSequential(new TankDriveWithEncoders (100.00));
//	AddSequential(new ResetEncodersWithPause(  0.50));
//	AddSequential(new StaticTurn            (-90.00));
}
