#ifndef _MIDTOSRPY1COMMAND_HG_
#define _MIDTOSRPY1COMMAND_HG_

#include <Timer.h>
#include <WPILib.h>
#include "../Profiles/MIDtoPY1Profile.h"
#include "../../CommandBase.h"

/**
 *
 */
class MIDtoPY1Command : public CommandBase
{
public:
	MIDtoPY1Command(Height::Type height = Height::NONE);
	~MIDtoPY1Command();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	MIDtoPY1Profile* pMotionProfiler;
	Height::Type htHeight = Height::NONE;
	Timer* pTimer;
};

#endif
