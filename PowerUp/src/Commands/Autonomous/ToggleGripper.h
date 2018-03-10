#ifndef _TOGGLEGRIPPER_HG_
#define _TOGGLEGRIPPER_HG_

#include <WPILib.h>
#include <Timer.h>
#include "../../CommandBase.h"

/**
 *
 */
class ToggleGripper : public CommandBase
{
public:
	ToggleGripper(double type);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	Timer* pTimer;
	double dType = 1;
};

#endif
