#ifndef _RCTOSLCOMMAND_HG_
#define _RCTOSLCOMMAND_HG_

#include <WPILib.h>
#include "../../CommandBase.h"
#include "../RCtoSLProfile.h"

/**
 *
 */
class RCtoSLCommand : public CommandBase
{
public:
	RCtoSLCommand();
	~RCtoSLCommand();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	RCtoSLProfile* pMotionProfiler;
};

#endif
