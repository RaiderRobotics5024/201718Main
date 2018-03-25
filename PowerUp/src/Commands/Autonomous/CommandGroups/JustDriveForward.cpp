
#include "JustDriveForward.h"
#include "../../../Utilities/Log.h"
#include "../DriveWithEncoders.h"
#include "../ResetEncodersWithPause.h"
#include "../TankDriveWithEncoders.h"

/**
 *
 */
JustDriveForward::JustDriveForward()
{
	LOG("[JustDriveForward] Constructed");

	AddSequential(new TankDriveWithEncoders (101.0, NONE, 4.0));
	AddSequential(new ResetEncodersWithPause(  10.0));
	LOG("[JustDriveForward] Finished!") ;
	return ;

//	AddSequential(new DriveWithEncoders(101.00, 1.0));
}
