#include "JustDriveForward.h"
#include "../../../Utilities/Log.h"
#include "../DriveWithEncoders.h"

/**
 *
 */
JustDriveForward::JustDriveForward()
{
	LOG("[JustDriveForward] Constructed");

	AddSequential(new DriveWithEncoders(140.00, 1.0, Height::NONE, 5.0));
}
