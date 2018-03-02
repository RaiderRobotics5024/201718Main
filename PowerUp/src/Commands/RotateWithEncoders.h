#ifndef _ROTATE_WITH_ENCODERS_HG_
#define _ROTATE_WITH_ENCODERS_HG_

#include <WPILib.h>
#include "../CommandBase.h"

/**
 *
 */
class RotateWithEncoders : public CommandBase
{
public:
	RotateWithEncoders(double distance, double speed);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	int iCounter = 0;
	double dDistance = 0;
	double dSpeed = 0;
};

#endif
