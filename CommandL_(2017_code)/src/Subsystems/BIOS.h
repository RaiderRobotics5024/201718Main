#ifndef BIOS_H
#define BIOS_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class BIOS: public Subsystem
{
private:
	Preferences* prefs;
	CANTalon* pCollectorMotor;
	CANTalon* pShooterMotorLeft;
	CANTalon* pShooterMotorRight;
	Timer* pTimer;
	DigitalInput* limitSwitch;
	Counter* counter;

	AnalogInput *frontUltra_p0;
	AnalogInput *frontUltra_p1;
	AnalogInput *frontUltra_p2;
	AnalogInput *frontUltra_p3;
	AnalogInput *frontUltra_p4;
	AnalogInput *frontUltra_p5;
	AnalogInput *frontUltra_p6;
	AnalogInput *frontUltra_p7;


public:
	BIOS();
	double GetTempFromPref();
	float fIntakeSpeed;
	float fShootSpeed;
	float fKickerSpeed;
	float fRegressionSpeed;

	void Intake(float speed);
	void Shoot(float speed);
	void LowGoal();
	float GetShootSpeed();
	float GetShootSpeed(double displacement);
	float GetIntakeSpeed();
	float GetShootSpeed_R(); //regression shooting
	float GetKickerSpeed();
	void StopShoot();
	void StopIntake();
	void RumbleWhenRange(double target, double variance);
	//util
	void InitDefaultCommand();
	void StartTimer();
	void StopTimer();
	bool IsSwitchSet();
	void InitializeCounter();
	double GetCurrentTime();
	double GetUltraAt(int port);
};

#endif
