#ifndef _Elevator_HG_
#define _Elevator_HG_

#include <WPILib.h>
#include <Commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include "../RobotMap.h"

class Elevator: public frc::Subsystem
{
public:
	Elevator();
	~Elevator();
	void InitDefaultCommand() override;
	void Reset();

private:
	can::WPI_TalonSRX* pElevatorMotor;

	//TODO: See how many hall effect switches there will be
	//DigitalInput* pLimit;
};

#endif
