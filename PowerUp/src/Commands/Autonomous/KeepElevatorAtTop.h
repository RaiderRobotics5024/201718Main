#ifndef _KEEPELEVATORATTOP_HG_
#define _KEEPELEVATORATTOP_HG_

#include <WPILib.h>
#include <Timer.h>
#include "../../CommandBase.h"
#include "../../Subsystems/Elevator.h"

/**
 *
 */
class KeepElevatorAtTop : public CommandBase
{
public:
	KeepElevatorAtTop();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	double dMotorSpeed = 0.0;
};

#endif
