#ifndef DriveTrain_H
#define DriveTrain_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class DriveTrain: public Subsystem
{
private:
	RobotDrive* pRobot;
	DigitalInput* pDipSwitchOne;
	DigitalInput* pDipSwitchTwo;
	DigitalInput* pDipSwitchThree;
	DigitalInput* pDipSwitchFour;
	DigitalOutput* pLED1;
	AnalogInput* pLeftFrontUltra;
	ADXRS450_Gyro* pGyro;
	double minErrorToMove;
	bool isReversed;
public:
	DriveTrain();
	bool IsReversed();
	void ReverseDrive(bool reverse);
	void InitDefaultCommand();
	void Drive(Joystick* stick);
	bool AutoTurn(double target, double kP);
	bool GoForward(double distance, float baseSpeed, double target, double kP);
	bool GoUltraForward(double distance, float baseSpeed, double target, double kP, double source);
	void Turn(float speed, float direction);
	void TankDrive(double leftAxis, double rightAxis);
	void LightLED();
	void Calibrate();
	int GetLeftEncoderValue();
	int GetRightEncoderValue();
	double GetRightSpeed();
	double GetLeftSpeed();
	double GetGyro();
	bool GetSwitchPositionOne();
	bool GetSwitchPositionTwo();
	bool GetSwitchPositionThree();
	bool GetSwitchPositionFour();
	void ResetGyro();
	CANTalon* pLeftFrontMotor;
	CANTalon* pLeftRearMotor;
	CANTalon* pRightFrontMotor;
	CANTalon* pRightRearMotor;
};

#endif
