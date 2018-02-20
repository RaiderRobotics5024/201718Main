#ifndef _CLIMB_SYSTEM_HG_
#define _CLIMB_SYSTEM_HG_

#include <WPILib.h>
#include <Commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include "../RobotMap.h"

/**
 *
 */

class ClimbSystem: public frc::Subsystem
{
public:
	ClimbSystem();
	~ClimbSystem();
	void InitDefaultCommand() override;
	void ExtendArm();
	void RetractArm();

private:
	can::WPI_TalonSRX* pClimbMotor;
	frc::Solenoid* pClimbSolenoid;
};

#endif
