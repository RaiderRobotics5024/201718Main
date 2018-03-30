#ifndef _RRTOSLCOMMAND_HG_
#define _RRTOSLCOMMAND_HG_

#include <Timer.h>
#include <WPILib.h>
#include "../Profiles/RRtoSLProfile.h"
#include "../../CommandBase.h"

/**
 *
 */
class RRtoSLCommand : public CommandBase
{
public:
	RRtoSLCommand(Height::Type height = Height::NONE);
	~RRtoSLCommand();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	RRtoSLProfile* pMotionProfiler;
	Height::Type htHeight = Height::NONE;
	Timer* pTimer;
};

#endif
