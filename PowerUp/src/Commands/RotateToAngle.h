#ifndef _ROTATE_TO_ANGLE_HG_
#define _ROTATE_TO_ANGLE_HG_

#include "../CommandBase.h"

class RotateToAngle : public CommandBase
{
public:
	RotateToAngle(double setpoint);
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
