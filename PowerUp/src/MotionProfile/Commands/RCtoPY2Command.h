#ifndef _RCTOSRPY2COMMAND_HG_
#define _RCTOSRPY2COMMAND_HG_

#include <Timer.h>
#include <WPILib.h>
#include "../Profiles/RCtoPY2Profile.h"
#include "../../CommandBase.h"

/**
 *
 */
class RCtoPY2Command : public CommandBase
{
public:
	RCtoPY2Command();
	~RCtoPY2Command();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	Timer* pTimer;
	RCtoPY2Profile* pMotionProfiler;
};

#endif
