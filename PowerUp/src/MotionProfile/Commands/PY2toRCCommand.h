#ifndef _PY2TORCCOMMAND_HG_
#define _PY2TORCCOMMAND_HG_

#include <Timer.h>
#include <WPILib.h>
#include "../Profiles/PY2toRCProfile.h"
#include "../../CommandBase.h"

/**
 *
 */
class PY2toRCCommand : public CommandBase
{
public:
	PY2toRCCommand(Height::Type height = Height::NONE);
	~PY2toRCCommand();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	PY2toRCProfile* pMotionProfiler;
	Height::Type htHeight = Height::NONE;
	Timer* pTimer;
};

#endif
