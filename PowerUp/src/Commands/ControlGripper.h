#ifndef _CONTROLGRIPPER_HG_
#define _CONTROLGRIPPER_HG_

#include <WPILib.h>
#include "../CommandBase.h"

class ControlGripper : public CommandBase
{
public:
	ControlGripper();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

};

#endif
