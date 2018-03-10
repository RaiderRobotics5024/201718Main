#ifndef _TOGGLEINTAKE_HG_
#define _TOGGLEINTAKE_HG_

#include <WPILib.h>
#include <Timer.h>
#include "../../CommandBase.h"

/**
 *
 */
class ToggleIntake : public CommandBase
{
public:
	ToggleIntake(double speed);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	Timer* pTimer;
	double dSpeed = 0;
};

#endif
