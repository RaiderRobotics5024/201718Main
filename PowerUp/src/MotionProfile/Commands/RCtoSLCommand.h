#ifndef _RCTOSLCOMMAND_HG_
#define _RCTOSLCOMMAND_HG_

#include <Timer.h>
#include <WPILib.h>
#include "../Profiles/RCtoSLProfile.h"
#include "../../CommandBase.h"

/**
 *
 */
class RCtoSLCommand : public CommandBase
{
public:
	RCtoSLCommand(Height::Type height = Height::NONE);
	~RCtoSLCommand();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	RCtoSLProfile* pMotionProfiler;
	Height::Type htHeight = Height::NONE;
	Timer* pTimer;
};

#endif
