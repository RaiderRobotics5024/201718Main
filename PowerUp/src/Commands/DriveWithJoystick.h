#ifndef _DRIVEWITHJOYSTICK_HG_
#define _DRIVEWITHJOYSTICK_HG_

#include <WPILib.h>
#include "../CommandBase.h"



class DriveWithJoystick: public CommandBase
{
public:
	DriveWithJoystick();
	~DriveWithJoystick();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	bool isDriveTest = true;
	double dDistance = 0.0;
	double dSetpoint = 0.0;
};

#endif
