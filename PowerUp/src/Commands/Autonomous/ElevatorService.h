#ifndef _ELEVATORSERVICE_HG_
#define _ELEVATORSERVICE_HG_

#include <WPILib.h>
#include <Timer.h>
#include "../../CommandBase.h"

/**
 *
 */
class ElevatorService : public CommandBase
{
public:
	ElevatorService();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	Timer* pTimer;
	double dMotorSpeed = 0.0;
	ElevatorHeight ehCalledTo = BOTTOM;
	bool   bArrived = false;
};

#endif
