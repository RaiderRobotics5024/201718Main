#ifndef _ELEVATOR_HG_
#define _ELEVATOR_HG_

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
	void SetMotorSpeed(double speed);

private:
	can::WPI_TalonSRX* pElevatorMotor;
	frc::DigitalInput* pTopElevatorSwitch;
	frc::DigitalInput pMidElevatorSwitch;
	frc::DigitalInput pBottomElevatorSwitch;

	//TODO: See how many hall effect switches there will be
	//DigitalInput* pLimit;
};

#endif
