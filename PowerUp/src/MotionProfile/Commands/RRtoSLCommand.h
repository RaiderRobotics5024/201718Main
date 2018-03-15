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
	RRtoSLCommand();
	~RRtoSLCommand();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	Timer* pTimer;
	RRtoSLProfile* pMotionProfiler;
};

#endif
