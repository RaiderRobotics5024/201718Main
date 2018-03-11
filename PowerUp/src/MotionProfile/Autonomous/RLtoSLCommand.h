#ifndef _RLTOSLCOMMAND_HG_
#define _RLTOSLCOMMAND_HG_

#include <Timer.h>
#include <WPILib.h>
#include "../../CommandBase.h"
#include "../RLtoSLProfile.h"

/**
 *
 */
class RLtoSLCommand : public CommandBase
{
public:
	RLtoSLCommand();
	~RLtoSLCommand();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	Timer* pTimer;
	RLtoSLProfile* pMotionProfiler;
};

#endif
