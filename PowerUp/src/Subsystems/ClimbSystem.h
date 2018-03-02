#ifndef _CLIMBSYSTEM_HG_
#define _CLIMBSYSTEM_HG_

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
	void ExtendArm(bool on);
	void RetractArm(double speed);

private:
	can::WPI_TalonSRX* pClimbMotor;
	frc::Solenoid* pClimbSolenoid;
};

#endif
