#ifndef _SRTORCCOMMAND_HG_
#define _SRTORCCOMMAND_HG_

#include <Timer.h>
#include <WPILib.h>
#include "../../CommandBase.h"
#include "../SRtoRCProfile.h"

/**
 *
 */
class SRtoRCCommand : public CommandBase
{
public:
	SRtoRCCommand();
	~SRtoRCCommand();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	Timer* pTimer;
	SRtoRCProfile* pMotionProfiler;
};

#endif
