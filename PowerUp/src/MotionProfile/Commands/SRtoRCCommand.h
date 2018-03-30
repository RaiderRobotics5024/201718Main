#ifndef _SRTORCCOMMAND_HG_
#define _SRTORCCOMMAND_HG_

#include <Timer.h>
#include <WPILib.h>
#include "../Profiles/SRtoRCProfile.h"
#include "../../CommandBase.h"

/**
 *
 */
class SRtoRCCommand : public CommandBase
{
public:
	SRtoRCCommand(Height::Type height = Height::NONE);
	~SRtoRCCommand();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	SRtoRCProfile* pMotionProfiler;
	Height::Type htHeight = Height::NONE;
	Timer* pTimer;
};

#endif
