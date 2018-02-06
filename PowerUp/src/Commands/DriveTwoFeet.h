#ifndef _DriveTwoFeet_HG_
#define _DriveTwoFeet_HG_

#include <iostream>
#include <WPILib.h>
#include "../RobotMap.h"
#include "../CommandBase.h"

/**
 *
 */

class DriveTwoFeet : public CommandBase
{
public:
	DriveTwoFeet();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	can::WPI_TalonSRX* _talon;
//	Joystick * _joy = new Joystick(0);
	std::string _sb;
	int _loops = 0;
	bool _lastButton1 = false;
	/** save the target position to servo to */
	double targetPositionRotations;
};

#endif
