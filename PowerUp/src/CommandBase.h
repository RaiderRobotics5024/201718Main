#ifndef _COMMANDBASE_HG_
#define _COMMANDBASE_HG_

#include <WPILib.h>
#include "Commands/Command.h"
#include "OI.h"
#include "Subsystems/DriveTrain.h"

/*
 *
 */
class CommandBase: public frc::Command
{
public:
	CommandBase();
	~CommandBase();

	static OI*                pOI;
	static DriveTrain*        pDriveTrain;
};

#endif
