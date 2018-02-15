#ifndef _DRIVEBYPOSITION_HG_
#define _DRIVEBYPOSITION_HG_

#include <WPILib.h>
#include "../CommandBase.h"

/**
 *
 */

class DriveByPosition : public CommandBase
{
public:
	DriveByPosition(double distance, double speed);
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
