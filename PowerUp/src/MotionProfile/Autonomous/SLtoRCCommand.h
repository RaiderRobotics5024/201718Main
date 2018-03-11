#ifndef _SLTORCCOMMAND_HG_
#define _SLTORCCOMMAND_HG_

#include <Timer.h>
#include <WPILib.h>
#include "../../CommandBase.h"
#include "../SLtoRCProfile.h"

/**
 *
 */
class SLtoRCCommand : public CommandBase
{
public:
	SLtoRCCommand();
	~SLtoRCCommand();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	Timer* pTimer;
	SLtoRCProfile* pMotionProfiler;
};

#endif
