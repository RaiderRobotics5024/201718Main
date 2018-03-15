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
	RCtoPY1Command();
	~RCtoPY1Command();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	Timer* pTimer;
	RCtoPY1Profile* pMotionProfiler;
};

#endif
