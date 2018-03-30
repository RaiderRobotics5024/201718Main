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
	RCtoPY2Command(Height::Type height = Height::NONE);
	~RCtoPY2Command();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	RCtoPY2Profile* pMotionProfiler;
	Height::Type htHeight = Height::NONE;
	Timer* pTimer;
};

#endif
