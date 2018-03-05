#ifndef _INTAKE_DRIVE_WITH_ENCODERS_HG_
#define _INTAKE_DRIVE_WITH_ENCODERS_HG_

#include <Timer.h>
#include <WPILib.h>
#include "../CommandBase.h"


/**
 *
 */
class IntakeDriveWithEncoders : public CommandBase
{
public:
	IntakeDriveWithEncoders(double distance, double speed);
	~IntakeDriveWithEncoders(void);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	Timer* pTimer;
	int iCounter = 0;
	double dDistance = 0;
	double dSpeed = 0;
	double dIntakeSpeed = 0;
};

#endif
