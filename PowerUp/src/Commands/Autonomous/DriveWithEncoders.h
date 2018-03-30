#ifndef _DRIVE_WITH_ENCODERS_HG_
#define _DRIVE_WITH_ENCODERS_HG_

#include <Timer.h>
#include <WPILib.h>
#include "../../CommandBase.h"
#include "../../Subsystems/Elevator.h"


/**
 *
 */
class DriveWithEncoders : public CommandBase
{
public:
	DriveWithEncoders(double distance, double speed, Height::Type height = Height::NONE, double timeout = 5.0);
	~DriveWithEncoders(void);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
	void Trace(void);

private:
	Timer* pTimer;
	int    iCounter = 0;
	double dDistance = 0;
	double dSpeed = 0;
	Height::Type htHeight = Height::NONE;
	double dTimeout = 5.0;
};

#endif
