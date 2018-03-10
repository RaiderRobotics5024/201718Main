#ifndef _RC2SRCOMMAND_HG_
#define _RC2SRCOMMAND_HG_

#include <WPILib.h>
#include "../../CommandBase.h"
#include "../RC2SRProfile.h"

/**
 *
 */
class RC2SRCommand : public CommandBase
{
public:
	RC2SRCommand();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	RC2SRProfile* pMotionProfiler;
};

#endif
