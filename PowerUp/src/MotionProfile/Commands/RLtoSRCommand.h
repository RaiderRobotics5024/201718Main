#ifndef _RLTOSRCOMMAND_HG_
#define _RLTOSRCOMMAND_HG_

#include <Timer.h>
#include <WPILib.h>
#include "../Profiles/RLtoSRProfile.h"
#include "../../CommandBase.h"

/**
 *
 */
class RLtoSRCommand : public CommandBase
{
public:
	RLtoSRCommand(Height::Type height = Height::NONE);
	~RLtoSRCommand();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	RLtoSRProfile* pMotionProfiler;
	Height::Type htHeight = Height::NONE;
	Timer* pTimer;
};

#endif
