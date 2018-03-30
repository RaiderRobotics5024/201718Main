#ifndef _RRTOSRCOMMAND_HG_
#define _RRTOSRCOMMAND_HG_

#include <Timer.h>
#include <WPILib.h>
#include "../Profiles/RRtoSRProfile.h"
#include "../../CommandBase.h"

/**
 *
 */
class RRtoSRCommand : public CommandBase
{
public:
	RRtoSRCommand(Height::Type height = Height::NONE);
	~RRtoSRCommand();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	RRtoSRProfile* pMotionProfiler;
	Height::Type htHeight = Height::NONE;
	Timer* pTimer;
};

#endif
