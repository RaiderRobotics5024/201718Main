#ifndef _MOVEELEVATOR_HG_
#define _MOVEELEVATOR_HG_

#include <WPILib.h>
#include <Timer.h>
#include "../../CommandBase.h"
#include "../../Subsystems/Elevator.h"

/**
 *
 */
class MoveElevator : public CommandBase
{
public:
	MoveElevator(Height::ElevatorHeight height);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
	void Trace();

private:
	Timer* pTimer;
	Height::ElevatorHeight ehHeight;
	double dMotorSpeed = 0.0;
};

#endif
