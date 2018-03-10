#ifndef _SR2RCCOMMAND_HG_
#define _SR2RCCOMMAND_HG_

#include <WPILib.h>
#include "../../CommandBase.h"
#include "../SR2RCProfile.h"

/**
 *
 */
class SR2RCCommand : public CommandBase
{
public:
	SR2RCCommand();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	SR2RCProfile* pMotionProfiler;
};

#endif
