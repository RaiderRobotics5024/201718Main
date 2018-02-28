#ifndef ExtendSFM_H
#define ExtendSFM_H

#include "../CommandBase.h"
#include "WPILib.h"

class ExtendSFM: public CommandBase
{
public:
	ExtendSFM();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
