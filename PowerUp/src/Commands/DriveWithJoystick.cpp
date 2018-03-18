#include "DriveWithJoystick.h"
#include "../Utilities/Log.h"
#include <math.h>
#include "../RobotMap.h"
#include <SmartDashboard/SmartDashboard.h>

/**
 *
 */
DriveWithJoystick::DriveWithJoystick()
{
	LOG("[DriveWithJoystick] Constructed");

	if (CommandBase::pDriveTrain != nullptr)
	{
		Requires(CommandBase::pDriveTrain);
	}
	else
	{
		LOG("[DriveWithJoystick] driveTrain is null!");
	}

	return;
}

/**
 *
 */
DriveWithJoystick::~DriveWithJoystick()
{
	LOG("[DriveWithJoystick] Destroyed");

	return;
}

/**
 *
 */
void DriveWithJoystick::Initialize()
{
	LOG("[DriveWithJoystick] Initialized");

	CommandBase::pDriveTrain->ResetGyro();
	CommandBase::pDriveTrain->ResetEncoders();
	CommandBase::pDriveTrain->InitAutonomousMode(true); // invert right front motor

	SmartDashboard::PutBoolean("Is Drive Test:", this->isDriveTest);

	return;
}

/**
 *
 */
void DriveWithJoystick::Execute()
{
	frc::XboxController* pJoyDrive = CommandBase::pOI->GetJoystickDrive();

	if (pJoyDrive->GetBumperPressed(XboxController::kLeftHand))
	{
		this->isDriveTest = !this->isDriveTest;
		SmartDashboard::PutBoolean("Is Drive Test:", this->isDriveTest);
	}

	if (pJoyDrive->GetYButtonPressed())
	{
		this->dDistance = 19.0;
		this->dSetpoint =  0.0;
	}
	else if (pJoyDrive->GetBButtonPressed())
	{
		this->dDistance = 80.0;
		this->dSetpoint = 90.0;
	}
	else if (pJoyDrive->GetAButtonPressed())
	{
		this->dDistance = 170.0;
		this->dSetpoint = 180.0;
	}
	else if (pJoyDrive->GetXButtonPressed())
	{
		this->dDistance = 230.0;
		this->dSetpoint = -90.0;
	}

	if (pJoyDrive->GetBumperPressed(XboxController::kRightHand))
	{
		if (this->isDriveTest)
		{
			double tp = SmartDashboard::GetNumber("Talon P:", 0.0);
			double ti = SmartDashboard::GetNumber("Talon I:", 0.0);
			double td = SmartDashboard::GetNumber("Talon D:", 0.0);
			double tf = SmartDashboard::GetNumber("Talon F:", 0.0);
			CommandBase::pDriveTrain->SetTalonPID(tp, ti, td, tf);

			CommandBase::pDriveTrain->Drive(dDistance, 1.0);
		}
		else
		{
			double gp = SmartDashboard::GetNumber("Gyro P:", 0.0);
			double gi = SmartDashboard::GetNumber("Gyro I:", 0.0);
			double gd = SmartDashboard::GetNumber("Gyro D:", 0.0);
			double gf = SmartDashboard::GetNumber("Gyro F:", 0.0);
			CommandBase::pDriveTrain->SetGyroPID(gp, gi, gd, gf);

			CommandBase::pDriveTrain->SetSetpoint(dSetpoint);
			CommandBase::pDriveTrain->Turn();
		}
	}

	if (this->isDriveTest)
	{
		LOG("[DriveWithJoystick] Target Distance: " << this->dDistance
				<< " Target Position: " << CommandBase::pDriveTrain->GetTargetPosition()
				<< " Current Postion: " << CommandBase::pDriveTrain->GetLeftPosition()
				<< " Velocity: " << CommandBase::pDriveTrain->GetVelocity()
				<< " P: " << SmartDashboard::GetNumber("Talon P:", 0.0));
	}
	else
	{
		LOG("[DriveWithJoystick] Set Point: " << this->dSetpoint
				<< " Current Angle: " << CommandBase::pDriveTrain->GetAngle()
				<< " Rate: " << CommandBase::pDriveTrain->GetRotateToAngleRate()
				<< " P: " << SmartDashboard::GetNumber("Gyro P:", 0.0));
	}

	return;
}

/**
 *
 */
bool DriveWithJoystick::IsFinished()
{
	return false;
}

/**
 *
 */
void DriveWithJoystick::End()
{
	return;
}

/**
 *
 */
void DriveWithJoystick::Interrupted()
{
	return;
}
