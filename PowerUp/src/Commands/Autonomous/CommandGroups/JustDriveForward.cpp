#include "JustDriveForward.h"
#include "../../../Utilities/Log.h"
#include "../DriveWithEncoders.h"
#include "../TankDriveWithEncoders.h"

/**
 *
 */
JustDriveForward::JustDriveForward()
{
	LOG("[JustDriveForward] Constructed");

	AddSequential(new TankDriveWithEncoders(101.00));
//	AddSequential(new DriveWithEncoders(101.00, 1.0));
}
