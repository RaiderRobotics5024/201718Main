#ifndef _BOTCLIMB_HG_
#define _BOTCLIMB_HG_

#include <WPILib.h>
#include <Commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include "../RobotMap.h"

class BotClimb: public frc::Subsystem
{
public:
	BotClimb();
	~BotClimb();
	void InitDefaultCommand() override;
	void Reset();

private:
	can::WPI_TalonSRX* pClimbMotor;

	//TODO: See how many hall effect switches there will be
	//DigitalInput* pLimit;
};

#endif
