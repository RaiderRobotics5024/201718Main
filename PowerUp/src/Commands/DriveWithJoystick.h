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
	
	double dTalon_F =  0.00; //0.118;
	double dTalon_P =  0.00; //0.02;
	double dTalon_I =  0.00;
	double dTalon_D =  0.00;

	double dGyro_P = 0.12; // Kc = 0.2
	double dGyro_I = 0.522; // 2 * Kp/Pc
	double dGyro_D = 1.2; // 0.125 * KpPc
};

#endif
