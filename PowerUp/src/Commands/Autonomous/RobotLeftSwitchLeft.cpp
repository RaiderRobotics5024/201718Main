#include "RobotLeftSwitchLeft.h"
#include "../DriveWithEncoders.h"

RobotLeftSwitchLeft::RobotLeftSwitchLeft()
{
	AddSequential(new DriveWithEncoders(120, 1.0));
}
