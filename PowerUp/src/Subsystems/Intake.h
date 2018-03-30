#ifndef _INTAKE_HG_
#define _INTAKE_HG_

#include <WPILib.h>
#include <Commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <DoubleSolenoid.h>

struct Action
{
	typedef enum
	{
		OPEN = 0,
		CLOSE
	} Type;
};

struct Cube
{
	typedef enum
	{
		EJECT = 0,
		TAKEIN
	} Type;
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
	void EjectCube(void);
	void TakeInCube(void);

	void SetSpeed(double speed);

private:
	can::WPI_TalonSRX* pLeftMotor;
	can::WPI_TalonSRX* pRightMotor;

	frc::DoubleSolenoid* pGripperSolenoid;
};

#endif
