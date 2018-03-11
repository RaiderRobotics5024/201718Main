#ifndef _RRTOSRCOMMAND_HG_
#define _RRTOSRCOMMAND_HG_

#include <Timer.h>
#include <WPILib.h>
#include "../../CommandBase.h"
#include "../RRtoSRProfile.h"

/**
 *
 */
class RRtoSRCommand : public CommandBase
{
public:
	RRtoSRCommand();
	~RRtoSRCommand();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	Timer* pTimer;
	RRtoSRProfile* pMotionProfiler;
};

#endif
