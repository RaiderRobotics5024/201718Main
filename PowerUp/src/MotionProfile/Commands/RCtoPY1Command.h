#ifndef _RCTOSRPY1COMMAND_HG_
#define _RCTOSRPY1COMMAND_HG_

#include <Timer.h>
#include <WPILib.h>
#include "../Profiles/RCtoPY1Profile.h"
#include "../../CommandBase.h"

/**
 *
 */
class RCtoPY1Command : public CommandBase
{
public:
	RCtoPY1Command(Height::Type height = Height::NONE);
	~RCtoPY1Command();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	RCtoPY1Profile* pMotionProfiler;
	Height::Type htHeight = Height::NONE;
	Timer* pTimer;
};

#endif
