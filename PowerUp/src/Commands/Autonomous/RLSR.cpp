#include "RLSR.h"
#include "../DriveByPosition.h"
#include "../RotateByPosition.h"

/**
 * Robot Left/Switch Right
 */

RLSR::RLSR()
{
	// 19.75 * pi / 4 = 15.51
	AddSequential(new DriveByPosition(60.0, 1.0));
	AddSequential(new RotateByPosition(15.51, 0.5));
	AddSequential(new DriveByPosition(120.0, 1.0));
	AddSequential(new RotateByPosition(15.51, 0.5));
	AddSequential(new DriveByPosition(24.0, 0.5));
}
