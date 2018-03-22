#ifndef _Tank_DRIVE_WITH_ENCODERS_HG_
#define _Tank_DRIVE_WITH_ENCODERS_HG_

#include <Timer.h>
#include <WPILib.h>
#include "../../CommandBase.h"


/**
 *
 */
class TankDriveWithEncoders : public CommandBase
{
public:
	TankDriveWithEncoders(double distance);
	~TankDriveWithEncoders(void);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	Timer* pTimer;
	int iCounter = 11;
	double dDistance = 0;
	double dLeftSpeed = 0;
	double dRightSpeed = 0;
	double rightInchesTraveled = 0;
	double leftInchesTraveled = 0;
//	double startingPosition;
	double rightEncoderPosition = 0;
	double leftEncoderPosition = 0;
	double accelTarget = 0;
	double minSpeed = 0.4;

	// For debugging
	int m_ExecuteCalledCount = 0;
	int m_IsFinishedCalledCount = 0;
};

#endif
