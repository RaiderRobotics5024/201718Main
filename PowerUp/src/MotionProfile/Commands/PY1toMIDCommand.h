#ifndef _PY1TORCCOMMAND_HG_
#define _PY1TORCCOMMAND_HG_

#include <Timer.h>
#include <WPILib.h>
#include "../Profiles/PY1toMIDProfile.h"
#include "../../CommandBase.h"

/**
 *
 */
class PY1toMIDCommand : public CommandBase
{
public:
	PY1toMIDCommand(Height::Type height = Height::NONE);
	~PY1toMIDCommand();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	PY1toMIDProfile* pMotionProfiler;
	Height::Type htHeight = Height::NONE;
	Timer* pTimer;
};

#endif
