#ifndef DoTheThing_H
#define DoTheThing_H

#include "../CommandBase.h"
#include "WPILib.h"

class DoTheThing: public CommandBase
{
public:
	DoTheThing();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
