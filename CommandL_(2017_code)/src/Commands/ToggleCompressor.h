#ifndef ToggleCompressor_H
#define ToggleCompressor_H

#include "../CommandBase.h"
#include "WPILib.h"

class ToggleCompressor: public CommandBase
{
public:
	bool isStart = isStart;
	ToggleCompressor(bool isStart);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
