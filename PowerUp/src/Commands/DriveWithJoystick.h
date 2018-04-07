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
	Timer* pTimer;
	bool   isDriveTest = false;
	bool   isTurnTest  = false;
	double dDistance = 0.0;
	double dSetpoint = 0.0;
	double dSpeed = 0.0;
	double dRotation = 0.0;
	double dLastDistance = 0.0;
	double dLastSetpoint = 0.0;
	double dMinDistance = 0.0;
	double dMaxDistance = 0.0;
	
	double dTalon_F =  0.001; //0.118;
	double dTalon_P =  0.06; //0.02;
	double dTalon_I =  0.00007;
	double dTalon_D =  0.60;

	double dGyro_P = 0.0082;
	double dGyro_I = 0.000; //0.001;
	double dGyro_D = 0.000; //0.10;
};

#endif
