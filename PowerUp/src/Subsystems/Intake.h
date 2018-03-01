#ifndef _INTAKE_HG_
#define _INTAKE_HG_

#include <WPILib.h>
#include <Commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <DoubleSolenoid.h>
#include "../RobotMap.h"

/**
 *
 */
class Intake: public frc::Subsystem
{
public:
	Intake();
	~Intake();
	void InitDefaultCommand() override;
	void Reset();

	void BeltIn(double);
	void BeltIntake(void);
	void BeltOff(void);
	void BeltOut(double);
	void CloseGripper(void);
	void OpenCloseIntake(void);

private:
	can::WPI_TalonSRX* pLeftMotor;
	can::WPI_TalonSRX* pRightMotor;

	frc::DoubleSolenoid* pGripperSolenoid;
};

#endif
