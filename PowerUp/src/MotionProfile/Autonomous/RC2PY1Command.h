#ifndef _RC2SRPY1COMMAND_HG_
#define _RC2SRPY1COMMAND_HG_

#include <WPILib.h>
#include "../../CommandBase.h"
#include "../RC2PY1Profile.h"

/**
 *
 */
class RC2PY1Command : public CommandBase
{
public:
	RC2PY1Command();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	RC2PY1Profile* pMotionProfiler;
};

#endif
