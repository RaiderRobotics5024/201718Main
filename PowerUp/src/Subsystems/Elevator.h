#ifndef _ELEVATOR_HG_
#define _ELEVATOR_HG_

#include <WPILib.h>
#include <Commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include "../RobotMap.h"

typedef enum eElevatorHeight
{
	NONE = 0, // doesn't matter where the elevator is, don't move it
	BOTTOM,   // elevator at the bottom or one cube height
	CUBEX2,   // elevator at cube on top of another cube height to intake - 19"
	SWITCH    // elevator at height to put cube in switch - 33"
} ElevatorHeight;

// Global Elevator Height variable
// Set this variable in any command and the elevator
// service will move the elevator to that height
extern ElevatorHeight gElevatorHeight;

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
