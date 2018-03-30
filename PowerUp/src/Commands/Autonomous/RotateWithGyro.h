#ifndef _ROTATE_WITH_GYRO_HG_
#define _ROTATE_WITH_GYRO_HG_

#include <Timer.h>
#include "../../CommandBase.h"
#include "../../Subsystems/Elevator.h"

class RotateWithGyro : public CommandBase
{
public:
	RotateWithGyro(double setpoint, Height::Type height = Height::NONE, double timeout = 3.0);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
	void Trace(void);

private:
	Timer* pTimer;
	int    iCounter = 0;
	double dSetpoint;
	Height::Type htHeight = Height::NONE;
	double dTimeout = 3.0;
};

#endif
