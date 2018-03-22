#ifndef StaticTurn_H
#define StaticTurn_H

#include <Timer.h>
#include "../CommandBase.h"
#include "../Subsystems/PID.h"
#include "../Utilities/Log.h"

class StaticTurn : public CommandBase
{
	#define PROPORTIONAL	0.005 // Tweaked value (Raw values when target=90 were ~90 decreasing to ~0 approaching target)
	#define INTEGRAL	0.004 // Tweaked value (Raw values when target=90 were ~0 increasing to ~90  approaching target)
	#define DERIVATIVE	0.002 // Tweaked value (Raw values when target=90 were ~0-~500 before values were tweaked(motors were at max speed))
	#define BUFFER_ZONE	0.3//Degrees
	#define TIMEOUT		3.0//Seconds

	Timer* m_pTimer ; /* Timer for timing out command if stuck */

	/* Personal PID for calculations */
	PID* m_pPID ;

	/* Personal target if you don't want to reset the target when finished (becuase target is reset in PID, not StaticTurn) */
	double target ;

	/* Angle to subtract the getYaw instead of zeroeing it to allow parallel use of the gyro */
	double yawOffset ;

	unsigned char counter ;

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
