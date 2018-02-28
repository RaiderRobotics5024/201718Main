#ifndef RumbleInRange_H
#define RumbleInRange_H

#include "../CommandBase.h"
#include "WPILib.h"

class RumbleInRange: public CommandBase
{
public:
	RumbleInRange();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
