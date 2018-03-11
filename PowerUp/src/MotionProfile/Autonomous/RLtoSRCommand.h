#ifndef _RLTOSRCOMMAND_HG_
#define _RLTOSRCOMMAND_HG_

#include <Timer.h>
#include <WPILib.h>
#include "../../CommandBase.h"
#include "../RLtoSRProfile.h"

/**
 *
 */
class RLtoSRCommand : public CommandBase
{
public:
	RLtoSRCommand();
	~RLtoSRCommand();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	Timer* pTimer;
	RLtoSRProfile* pMotionProfiler;
};

#endif
