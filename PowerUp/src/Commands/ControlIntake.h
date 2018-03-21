#ifndef _CONTROLINTAKE_HG_
#define _CONTROLINTAKE_HG_

#include <WPILib.h>
#include "../CommandBase.h"

class ControlIntake : public CommandBase
{
public:
	ControlIntake();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

};

#endif
