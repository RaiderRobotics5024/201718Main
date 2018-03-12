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
	void Trace(void);

private:
	Timer* pTimer;
	int iCounter = 0;
	RCtoSRProfile* pMotionProfiler;
};

#endif
