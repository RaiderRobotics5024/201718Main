#ifndef StaticTurn_H
#define StaticTurn_H

#include <Timer.h>
#include "../CommandBase.h"
#include "../Subsystems/PID.h"
#include "../Utilities/Log.h"

class StaticTurn : public CommandBase
{
	#define PROPORTIONAL	0.020 // Tweaked value (Raw values are = target decreasing to 0 when approaching target)
	#define INTEGRAL	0.012 // Tweaked value (Raw values are 0 increasing the further away from target)
	#define DERIVATIVE	0.002 // Tweaked value (Raw values depend on speed at instance. Init val will be ~5000 while gyro is resetting)
	#define BUFFER_ZONE	0.4//Degrees
	#define TIMEOUT		3.0//Seconds

	/* Timer for timing out command if stuck */
	Timer* m_pTimer ;

	/* Personal PID for calculations */
	PID* m_pPID ;

	/* Personal target if you don't want to reset the target when finished (becuase target is reset in PID, not StaticTurn) */
	double target ;

	/* Angle to subtract the getYaw instead of zeroeing it to allow parallel use of the gyro */
	double yawOffset ;

	int counter ;

public:
	StaticTurn();
	StaticTurn(double) ;
	~StaticTurn() ;
	void setTarget(double deg) ;
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // StaticTurn_H
