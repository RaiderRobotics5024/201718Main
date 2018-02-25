#ifndef _CLIMBSCALE_HG_
#define _CLIMBSCALE_HG_

#include <WPILib.h>
#include "../CommandBase.h"

/**
 *
 */
class ClimbScale : public CommandBase
{
public:
	ClimbScale();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

};

#endif
