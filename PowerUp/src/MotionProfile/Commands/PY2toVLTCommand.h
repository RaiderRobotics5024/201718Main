#ifndef _PY2TOVLTCOMMAND_HG_
#define _PY2TOVLTCOMMAND_HG_

#include <Timer.h>
#include <WPILib.h>
#include "../Profiles/PY2toVLTProfile.h"
#include "../../CommandBase.h"

/**
 *
 */
class PY2toVLTCommand : public CommandBase
{
public:
	PY2toVLTCommand(Height::Type height = Height::NONE);
	~PY2toVLTCommand();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	PY2toVLTProfile* pMotionProfiler;
	Height::Type htHeight = Height::NONE;
	Timer* pTimer;
};

#endif
