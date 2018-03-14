#ifndef _TOGGLEGRIPPER_HG_
#define _TOGGLEGRIPPER_HG_

#include <WPILib.h>
#include <Timer.h>
#include "../../CommandBase.h"
#include "../../Subsystems/Intake.h"

/**
 *
 */
class ToggleGripper : public CommandBase
{
public:
	ToggleGripper(Action::GripperAction state);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	Timer* pTimer;
	Action::GripperAction gsState;
};

#endif
