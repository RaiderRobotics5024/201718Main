#ifndef _OPENCLOSEGRIPPER_HG_
#define _OPENCLOSEGRIPPER_HG_

#include <WPILib.h>
#include <Timer.h>
#include "../CommandBase.h"

/**
 *
 */
class OpenCloseGripper : public CommandBase
{
public:
	OpenCloseGripper(double type);
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
