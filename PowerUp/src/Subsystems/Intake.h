#ifndef SRC_SUBSYSTEMS_INTAKE_H_
#define SRC_SUBSYSTEMS_INTAKE_H_

#include <WPILib.h>
#include <Commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <DoubleSolenoid.h>
#include "../RobotMap.h"

#include <iostream>

class Intake: public frc::Subsystem
{
public:
	Intake();
	~Intake();
	void InitDefaultCommand() override;
	void Reset();
//	void SetMotorSpeed(double leftSpeed, double rightSpeed);
	void OpenCloseIntake(void);
	void BeltIntake(void);

	static const double SPEED_ADJUSTMENT_RATIO;// Can't define values here (unless int) see .cpp file

private:
	can::WPI_TalonSRX* pLeftMotor;
	can::WPI_TalonSRX* pRightMotor;

	frc::DoubleSolenoid* pGripperSolenoid;
};


#endif /* SRC_SUBSYSTEMS_INTAKE_H_ */
