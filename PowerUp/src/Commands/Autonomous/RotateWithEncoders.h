#ifndef _ROTATE_WITH_ENCODERS_HG_
#define _ROTATE_WITH_ENCODERS_HG_

#include <Timer.h>
#include <WPILib.h>
#include "../../CommandBase.h"
#include "../../Subsystems/Elevator.h"

/**
 *
 */
class RotateWithEncoders : public CommandBase
{
public:
	RotateWithEncoders(double distance, double speed, Height::Type height = Height::NONE, double timeout = 5.0);
	~RotateWithEncoders(void);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
	void Trace(void);

private:
	Timer* pTimer;
	int    iCounter = 0;
	double dDistance = 0.0;
	double dSpeed = 0.0;
	Height::Type htHeight = Height::NONE;
	double dTimeout = 5.0;
};

#endif
