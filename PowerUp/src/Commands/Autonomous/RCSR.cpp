#include "RCSR.h"
#include "../../Utilities/Log.h"
#include "../DriveByPosition.h"
#include "../RotateByPosition.h"

/**
 * Robot Centre/Switch Right
 */

RCSR::RCSR()
{
	LOG("[RCSR] Constructed");

	AddSequential(new DriveByPosition(60.0, 1.0));
}
