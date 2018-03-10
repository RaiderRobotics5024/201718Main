#ifndef _RC2SLCOMMAND_HG_
#define _RC2SLCOMMAND_HG_

#include <WPILib.h>
#include "../../CommandBase.h"
#include "../RC2SLProfile.h"

/**
 *
 */
class RC2SLCommand : public CommandBase
{
public:
	RC2SLCommand();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	RC2SLProfile* pMotionProfiler;
};

#endif
