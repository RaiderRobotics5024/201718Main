#ifndef _SRTOMIDCOMMAND_HG_
#define _SRTOMIDCOMMAND_HG_

#include <Timer.h>
#include <WPILib.h>
#include "../Profiles/SRtoMIDProfile.h"
#include "../../CommandBase.h"

/**
 *
 */
class SRtoMIDCommand : public CommandBase
{
public:
	SRtoMIDCommand(Height::Type height = Height::NONE);
	~SRtoMIDCommand();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	SRtoMIDProfile* pMotionProfiler;
	Height::Type htHeight = Height::NONE;
	Timer* pTimer;
};

#endif
