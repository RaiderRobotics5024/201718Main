#ifndef _PY12RCCOMMAND_HG_
#define _PY12RCCOMMAND_HG_

#include <WPILib.h>
#include "../../CommandBase.h"
#include "../PY12RCProfile.h"

/**
 *
 */
class PY12RCCommand : public CommandBase
{
public:
	PY12RCCommand();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	PY12RCProfile* pMotionProfiler;
};

#endif
