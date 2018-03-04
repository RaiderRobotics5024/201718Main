#ifndef StaticTurn_H
#define StaticTurn_H

#include <Timer.h>
#include "../CommandBase.h"
#include "../Subsystems/PID.h"
#include "../Utilities/Log.h"

class StaticTurn : public CommandBase
{
	#define PROPORTIONAL	0.005
	#define INTEGRAL	0.003
	#define DERIVATIVE	0.001
	#define BUFFER_ZONE	0.5 //Degrees
	#define TIMEOUT		5 //Seconds

	Timer* timer ;
	PID* m_PID ;
	double target ;
	int iCounter = 0;

public:
	StaticTurn();
	StaticTurn(double) ;
	double setTarget(double deg) ;
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // StaticTurn_H
