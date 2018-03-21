#ifndef _ELEVATOR_HG_
#define _ELEVATOR_HG_

#include <WPILib.h>
#include <Commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include "../RobotMap.h"

struct Height
{
	typedef enum
	{
		BOTTOM = 1, // elevator at the bottom or one cube height
		CUBEX2,     // elevator at cube on top of another cube height to intake - 19"
		SWITCH      // elevator at height to put cube in switch - 33"
	} ElevatorHeight;
};

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
	void SetMotorSpeed(double speed);


private:
	can::WPI_TalonSRX* pElevatorMotor;

	frc::DigitalInput* pTopSwitch;
	frc::DigitalInput* pMiddleSwitch;
	frc::DigitalInput* pBottomSwitch;
};

#endif
