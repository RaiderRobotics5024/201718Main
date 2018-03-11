#ifndef _RCTOSRCOMMAND_HG_
#define _RCTOSRCOMMAND_HG_

#include <Timer.h>
#include <WPILib.h>
#include "../../CommandBase.h"
#include "../RCtoSRProfile.h"

/**
 *
 */
class RCtoSRCommand : public CommandBase
{
public:
	RCtoSRCommand();
	~RCtoSRCommand();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	Timer* pTimer;
	RCtoSRProfile* pMotionProfiler;
};

#endif
