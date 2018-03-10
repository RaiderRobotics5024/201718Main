#ifndef _ELEVATOR_HG_
#define _ELEVATOR_HG_

#include <WPILib.h>
#include <Commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include "../RobotMap.h"

/**
 *
 */
class Elevator: public frc::Subsystem
{
public:
	Elevator();
	~Elevator();
	void InitDefaultCommand() override;
	void Reset();

	bool IsTopSwitchAligned(void);
	bool IsMiddleSwitchAligned(void);
	bool IsBottomSwitchAligned(void);
	void ResetCounters(void);
	void SetMotorSpeed(double speed);

private:
	can::WPI_TalonSRX* pElevatorMotor;

	frc::DigitalInput* pTopSwitch;
	frc::DigitalInput* pMiddleSwitch;
	frc::DigitalInput* pBottomSwitch;
	Counter* pTopCounter;
	Counter* pMiddleCounter;
	Counter* pBottomCounter;
};

#endif
