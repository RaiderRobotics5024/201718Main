#ifndef _EJECTCUBE_HG_
#define _EJECTCUBE_HG_

#include <WPILib.h>
#include "../CommandBase.h"

/**
 *
 */
class EjectCube : public CommandBase
{
public:
	EjectCube(double speed);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	double dSpeed = 0;
};

#endif
