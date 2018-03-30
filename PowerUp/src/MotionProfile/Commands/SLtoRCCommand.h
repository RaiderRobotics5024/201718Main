#ifndef _SLTORCCOMMAND_HG_
#define _SLTORCCOMMAND_HG_

#include <Timer.h>
#include <WPILib.h>
#include "../Profiles/SLtoRCProfile.h"
#include "../../CommandBase.h"

/**
 *
 */
class SLtoRCCommand : public CommandBase
{
public:
	SLtoRCCommand(Height::Type height = Height::NONE);
	~SLtoRCCommand();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	SLtoRCProfile* pMotionProfiler;
	Height::Type htHeight = Height::NONE;
	Timer* pTimer;
};

#endif
