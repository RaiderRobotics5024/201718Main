#ifndef Turn_H
#define Turn_H

#include "../CommandBase.h"
#include "WPILib.h"

class Turn: public CommandBase
{
public:
	Turn(double target, double kP);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	double target;
	double kP;
};

#endif
