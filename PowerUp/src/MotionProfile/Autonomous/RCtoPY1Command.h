#ifndef _RCTOSRPY1COMMAND_HG_
#define _RCTOSRPY1COMMAND_HG_

#include <WPILib.h>
#include "../../CommandBase.h"
#include "../RCtoPY1Profile.h"

/**
 *
 */
class RCtoPY1Command : public CommandBase
{
public:
	RCtoPY1Command();
	~RCtoPY1Command();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	RCtoPY1Profile* pMotionProfiler;
};

#endif
