#ifndef _DRIVE_TRAIN_HG_
#define _DRIVE_TRAIN_HG_

#include <string>
#include <WPILib.h>
#include <Commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <Drive/DifferentialDrive.h>
#include <AHRS.h>

/**
 *
 */

class DriveTrain: public frc::Subsystem, PIDOutput
{
public:
	DriveTrain();
	~DriveTrain();
	void InitAutonomous(bool inverted);
	void InitDefaultCommand() override;
	void Drive(XboxController* joystick);
	void Drive(double distance, double speed);
	void Turn(double setpoint);

	// These are the same as the DifferentialDrive class:
	void ArcadeDrive( double xSpeed, double zRotation );
	void CurvatureDrive( double xSpeed, double zRotation, bool isQuickTurn );
	void TankDrive( double leftSpeed, double rightSpeed );

	double GetAngle();
	double GetLeftPosition();
	double GetRightPosition();
	bool IsDriving();
	bool IsTurning();

	void ResetDrive();
	void ResetEncoders();
	void ResetGyro();

	void Trace();
	void Trace(WPI_TalonSRX* pTalonSRX, const std::string name);

	virtual void PIDWrite(double output);


private:
	can::WPI_TalonSRX* pLeftFrontMotor;
	can::WPI_TalonSRX* pLeftRearMotor;
	can::WPI_TalonSRX* pRightFrontMotor;
	can::WPI_TalonSRX* pRightRearMotor;

	frc::DifferentialDrive* pRobotDrive;

	AHRS* pGyro; // navX MXP
	PIDController* pTurnController;

	double dRotateToAngleRate;
};

#endif
