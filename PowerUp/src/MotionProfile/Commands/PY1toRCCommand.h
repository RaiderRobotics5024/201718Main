#ifndef _PY1TORCCOMMAND_HG_
#define _PY1TORCCOMMAND_HG_

#include <Timer.h>
#include <WPILib.h>
#include "../Profiles/PY1toRCProfile.h"
#include "../../CommandBase.h"

/**
 *
 */
class PY1toRCCommand : public CommandBase
{
public:
	PY1toRCCommand();
	~PY1toRCCommand();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	Timer* pTimer;
	PY1toRCProfile* pMotionProfiler;
};

#endif
