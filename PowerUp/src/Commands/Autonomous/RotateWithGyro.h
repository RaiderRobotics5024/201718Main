#ifndef _ROTATE_WITH_GYRO_HG_
#define _ROTATE_WITH_GYRO_HG_

#include <Timer.h>
#include "../../CommandBase.h"

class RotateWithGyro : public CommandBase
{
public:
	RotateWithGyro(double setpoint);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
	void Trace(void);

private:
	Timer* pTimer;
	int iCounter = 0;
	double dSetPoint;
};

#endif
