#ifndef SRC_CLIMBSYSTEM_H_
#define SRC_CLIMBSYSTEM_H_

#include <WPILib.h>
#include <Commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include "../RobotMap.h"

class ClimbSystem: public frc::Subsystem
{
public:
	ClimbSystem();
	~ClimbSystem();
	void InitDefaultCommand() override;
//	void Reset();
	void ExtendArm(void);
	void RetractArm(void);
private:

	can::WPI_TalonSRX* pClimbMotor;
	frc::Solenoid* pClimbSolenoid;
};



#endif /* SRC_SUBSYSTEMS_CLIMBSYSTEM_H_ */
