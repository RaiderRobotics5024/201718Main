#ifndef _TOGGLEINTAKE_HG_
#define _TOGGLEINTAKE_HG_

#include <WPILib.h>
#include <Timer.h>
#include "../../CommandBase.h"
#include "../../Subsystems/Intake.h"

/**
 *
 */
class ToggleIntake : public CommandBase
{
public:
	ToggleIntake(Cube::Type cube);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	Timer* pTimer;
	Cube::Type ctCube;
};

#endif
