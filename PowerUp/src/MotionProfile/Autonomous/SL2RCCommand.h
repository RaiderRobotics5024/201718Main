#ifndef _SL2RCCOMMAND_HG_
#define _SL2RCCOMMAND_HG_

#include <WPILib.h>
#include "../../CommandBase.h"
#include "../SL2RCProfile.h"

/**
 *
 */
class SL2RCCommand : public CommandBase
{
public:
	SL2RCCommand();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	SL2RCProfile* pMotionProfiler;
};

#endif
