#ifndef _MOTIONPROFILECOMMAND_HG_
#define _MOTIONPROFILECOMMAND_HG_

#include <WPILib.h>
#include "../../CommandBase.h"
#include "../../MotionProfile/MotionProfiler.h"

/**
 *
 */
class MotionProfileCommand : public CommandBase
{
public:
	MotionProfileCommand();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	MotionProfiler* pMotionProfiler;
};

#endif
