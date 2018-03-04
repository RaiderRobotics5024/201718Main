#ifndef _CONTROLELEVATOR_HG_
#define _CONTROLELEVATOR_HG_

#include <WPILib.h>
#include "../CommandBase.h"

/**
 *
 */
class ControlElevator : public CommandBase
{
public:
	ControlElevator();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	void Trace(double speed);
	int iCounter = 0;
	int setElevatorPos;
	int lastElevatorPos;
};

#endif
