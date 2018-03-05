#ifndef _MOVEELEVATOR_HG_
#define _MOVEELEVATOR_HG_

#include <WPILib.h>
#include <Timer.h>
#include "../CommandBase.h"

/**
 *
 */
class MoveElevator : public CommandBase
{
public:
	MoveElevator(double pos);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	Timer* pTimer;
	double dPos = 0;
};

#endif
