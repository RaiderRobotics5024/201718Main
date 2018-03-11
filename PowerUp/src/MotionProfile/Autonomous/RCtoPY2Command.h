#ifndef _RCTOSRPY2COMMAND_HG_
#define _RCTOSRPY2COMMAND_HG_

#include <WPILib.h>
#include "../../CommandBase.h"
#include "../RCtoPY2Profile.h"

/**
 *
 */
class RCtoPY2Command : public CommandBase
{
public:
	RCtoPY2Command();
	~RCtoPY2Command();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	RCtoPY2Profile* pMotionProfiler;
};

#endif
