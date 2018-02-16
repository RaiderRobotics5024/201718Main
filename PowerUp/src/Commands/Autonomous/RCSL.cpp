#include "RCSL.h"
#include "../../Utilities/Log.h"
#include "../DriveByPosition.h"
#include "../RotateToAngle.h"

/**
 * Robot Centre/Switch Left
 */

RCSL::RCSL()
{
	LOG("[RCSL] Constructed");

	AddSequential(new DriveByPosition(60.0, 1.0));
	AddSequential(new RotateToAngle(-90.0f));
	AddSequential(new DriveByPosition(240.0, 1.0));
	AddSequential(new RotateToAngle(90.0f));
	AddSequential(new DriveByPosition(24.0, 0.5));
}
