#ifndef _ROTATE_WITH_GYRO_HG_
#define _ROTATE_WITH_GYRO_HG_

#include "../CommandBase.h"

class RotateWithGyro : public CommandBase
{
public:
	RotateWithGyro(double setpoint);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	int iCounter = 0;
	double dSetPoint;
};

#endif
