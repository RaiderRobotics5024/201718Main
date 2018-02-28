#ifndef ShootLowGoal_H
#define ShootLowGoal_H

#include "../CommandBase.h"
#include "WPILib.h"

class ShootLowGoal: public CommandBase
{
public:
	ShootLowGoal();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
