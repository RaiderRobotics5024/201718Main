#ifndef _PY2TOMIDCOMMAND_HG_
#define _PY2TOMIDCOMMAND_HG_

#include <MotionProfile/Profiles/PY2toMIDProfile.h>
#include <Timer.h>
#include <WPILib.h>
#include "../../CommandBase.h"

/**
 *
 */
class PY2toMIDCommand : public CommandBase
{
public:
	PY2toMIDCommand(Height::Type height = Height::NONE);
	~PY2toMIDCommand();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	PY2toMIDProfile* pMotionProfiler;
	Height::Type htHeight = Height::NONE;
	Timer* pTimer;
};

#endif
