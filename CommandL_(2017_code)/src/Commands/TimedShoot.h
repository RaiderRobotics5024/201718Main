#ifndef TimedShoot_H
#define TimedShoot_H

#include "../CommandBase.h"
#include "WPILib.h"

class TimedShoot: public CommandBase
{
public:
	TimedShoot();
	TimedShoot(double displacement);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	double displacement;
};

#endif
