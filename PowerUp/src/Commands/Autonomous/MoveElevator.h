#ifndef _MOVEELEVATOR_HG_
#define _MOVEELEVATOR_HG_

#include <WPILib.h>
#include <Timer.h>
#include "../../CommandBase.h"

/**
 *
 */
class MoveElevator : public CommandBase
{
public:
	MoveElevator(int position);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	Timer* pTimer;
	int    dPosition = 0;
	double dMotorSpeed = 0.0;
};

#endif
