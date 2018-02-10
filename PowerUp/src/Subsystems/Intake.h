#ifndef _INTAKE_HG_
#define _INTAKE_HG_

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
	void SetMotorSpeed(double leftSpeed,double rightSpeed);

private:
	can::WPI_TalonSRX* pLeftMotor;
	can::WPI_TalonSRX* pRightMotor;

	frc::DoubleSolenoid* pGripperSolenoid;

	//TODO: See how many hall effect switches there will be
	//DigitalInput* pLimit;
};

#endif
