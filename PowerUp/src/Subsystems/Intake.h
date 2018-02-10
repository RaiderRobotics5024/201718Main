#ifndef _DRIVETRAIN_HG_
#define _DRIVETRAIN_HG_

#include <WPILib.h>
#include <Commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include "../RobotMap.h"

class Intake: public frc::Subsystem
{
public:
	Intake();
	~Intake();
	void InitDefaultCommand() override;
	void Reset();

private:
	can::WPI_TalonSRX* pLeftMotor;
	can::WPI_TalonSRX* pRightMotor;

};

#endif
