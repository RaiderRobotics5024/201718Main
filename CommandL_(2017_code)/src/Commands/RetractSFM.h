#ifndef RetractSFM_H
#define RetractSFM_H

#include "../CommandBase.h"
#include "WPILib.h"

class RetractSFM: public CommandBase
{
public:
	RetractSFM();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
