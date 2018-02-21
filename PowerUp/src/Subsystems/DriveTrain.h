#ifndef _DRIVETRAIN_HG_
#define _DRIVETRAIN_HG_

#include <WPILib.h>
#include <Commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <SpeedControllerGroup.h>
#include <Drive/DifferentialDrive.h>
#include "../RobotMap.h"

#include <iostream>


class DriveTrain: public frc::Subsystem
{
public:
	DriveTrain();
	~DriveTrain();
	void InitDefaultCommand() override;

	// Original basic example drive, passing joystick. Calls ArcadeDrive()
	void Drive(XboxController* joystick);
	// These are the same as the DifferentialDrive class:
	void ArcadeDrive( double xSpeed, double zRotation );
	void CurvatureDrive( double xSpeed, double zRotation, bool isQuickTurn );
	void TankDrive( double leftSpeed, double rightSpeed );

	void Reset();

private:
	can::WPI_TalonSRX* pLeftFrontMotor;
	can::WPI_TalonSRX* pLeftRearMotor;
	can::WPI_TalonSRX* pRightFrontMotor;
	can::WPI_TalonSRX* pRightRearMotor;

	frc::SpeedControllerGroup* pLeftSpeedControllerGroup;
	frc::SpeedControllerGroup* pRightSpeedControllerGroup;

	frc::DifferentialDrive* pRobotDrive;
};

#endif
