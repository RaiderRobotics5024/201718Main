#ifndef _PY1TORCCOMMAND_HG_
#define _PY1TORCCOMMAND_HG_

#include <WPILib.h>
#include "../../CommandBase.h"
#include "../PY1toRCProfile.h"

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
	PY1toRCProfile* pMotionProfiler;
};

#endif
