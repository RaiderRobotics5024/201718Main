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
	PY2toVLTCommand();
	~PY2toVLTCommand();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	Timer* pTimer;
	PY2toVLTProfile* pMotionProfiler;
};

#endif
