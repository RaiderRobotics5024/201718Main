#ifndef ReverseDrive_H
#define ReverseDrive_H

#include "../CommandBase.h"
#include "WPILib.h"

class ReverseDrive: public CommandBase
{
public:
	ReverseDrive();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
