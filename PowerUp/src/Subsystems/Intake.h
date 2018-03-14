#ifndef _INTAKE_HG_
#define _INTAKE_HG_

#include <WPILib.h>
#include <Commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <DoubleSolenoid.h>
#include "../RobotMap.h"

struct Action
{
	typedef enum
	{
		OPEN = 0,
		CLOSE
	} GripperAction;
};

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

	void CloseGripper(void);
	void OpenGripper(void);
	void SetSpeed(double);

private:
	can::WPI_TalonSRX* pLeftMotor;
	can::WPI_TalonSRX* pRightMotor;

	frc::DoubleSolenoid* pGripperSolenoid;
};

#endif
