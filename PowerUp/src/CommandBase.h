#ifndef _COMMANDBASE_HG_
#define _COMMANDBASE_HG_

#include <iostream>
#include <WPILib.h>
#include "Commands/Command.h"
#include "OI.h"
#include "Subsystems/DriveTrain.h"
#include "Subsystems/Intake.h"
#include "Subsystems/Elevator.h"

/**
 *
 */

class CommandBase: public frc::Command
{
public:
	CommandBase();
	~CommandBase();
	CommandBase(char const *name);
	static void init();
	static OI *pOI;
	static DriveTrain *pDriveTrain;
	static Intake *pIntake;
	static Elevator *pElevator;
};

#endif
