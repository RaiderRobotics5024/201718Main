#ifndef _RCTOSRCOMMAND_HG_
#define _RCTOSRCOMMAND_HG_

#include <Timer.h>
#include <WPILib.h>
#include "../Profiles/RCtoSRProfile.h"
#include "../../CommandBase.h"

/**
 *
 */
class RCtoSRCommand : public CommandBase
{
public:
	RCtoSRCommand(Height::Type height = Height::NONE);
	~RCtoSRCommand();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
	void Trace(void);

private:
	RCtoSRProfile* pMotionProfiler;
	Height::Type htHeight = Height::NONE;
	Timer* pTimer;
};

#endif
