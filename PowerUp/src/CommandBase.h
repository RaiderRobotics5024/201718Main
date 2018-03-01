#ifndef _COMMANDBASE_HG_
#define _COMMANDBASE_HG_

#include <WPILib.h>
#include "Commands/Command.h"
#include "OI.h"
#include "Subsystems/DriveTrain.h"
#include "Subsystems/Intake.h"
#include "Subsystems/Elevator.h"
#include "Subsystems/ClimbSystem.h"
#include <Subsystems/CompressorSystem.h>

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
	static Intake*            pIntake;
	static Elevator*          pElevator;
	static ClimbSystem*       pClimbSystem;
	static CompressorSystem*  pCompressorSystem;
};

#endif
