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

	this->pTimer = new Timer();

	return;
}

/**
 *
 */
DriveWithJoystick::~DriveWithJoystick()
{
	LOG("[DriveWithJoystick] Destroyed");

	delete this->pTimer;

	return;
}

/**
 *
 */
void DriveWithJoystick::Initialize()
{
	LOG("[DriveWithJoystick] Initialized");

	return;
}

/**
 *
 */
void DriveWithJoystick::Execute()
{
	frc::XboxController* pJoyDrive = CommandBase::pOI->GetJoystickDrive();

	// use right bumper to turn on/off drive test
	if (pJoyDrive->GetBumperPressed(XboxController::kRightHand))
	{
		this->isDriveTest = !this->isDriveTest;
		this->isTurnTest = false;
		
		SmartDashboard::PutBoolean("Is Drive Test:", this->isDriveTest);
		SmartDashboard::PutBoolean("Is Turn  Test:", this->isTurnTest);

		if(this->isDriveTest)
		{
			CommandBase::pDriveTrain->InitAutonomousMode(true);
		}
		else
		{
			CommandBase::pDriveTrain->ResetDrive();
		}
	}

	// use left bumper to turn on/off turn test
	if (pJoyDrive->GetBumperPressed(XboxController::kLeftHand))
	{
		this->isTurnTest = !this->isTurnTest;
		this->isDriveTest = false;
		
		SmartDashboard::PutBoolean("Is Drive Test:", this->isDriveTest);
		SmartDashboard::PutBoolean("Is Turn  Test:", this->isTurnTest);

		if(this->isTurnTest)
		{
			CommandBase::pDriveTrain->InitAutonomousMode(false);
		}
		else
		{
			CommandBase::pDriveTrain->ResetDrive();
		}
	}

	// Y, B, A, X buttons set test distances and angles
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

	// use right trigger to get/set the PID values and start the drive or turn test
	if (pJoyDrive->GetTriggerAxis(frc::XboxController::kRightHand))
	{
		if (this->isDriveTest)
		{
			this->pTimer->Reset();
			this->pTimer->Start();
			
			CommandBase::pDriveTrain->ResetEncoders();
			CommandBase::pDriveTrain->Drive(dDistance, 1.0);
		}
		else if (this->isTurnTest)
		{
			this->pTimer->Reset();
			this->pTimer->Start();
			
			CommandBase::pDriveTrain->ResetGyro();
			CommandBase::pDriveTrain->SetSetpoint(dSetpoint);
			CommandBase::pDriveTrain->Turn();
		}
	}
	
	// drive the bot as usual if not drive test and not turn test
	if (!this->isDriveTest && !this->isTurnTest)
	{
		double xSpeed    = pJoyDrive->GetX(XboxController::kLeftHand);
		double zRotation = pJoyDrive->GetY(XboxController::kLeftHand);

		if (fabs(xSpeed) <= XBOX_DEADZONE_LEFT_JOY)
		{
			xSpeed = 0.0;
		}

		if (fabs(zRotation) <= XBOX_DEADZONE_LEFT_JOY)
		{
			zRotation = 0.0;
		}

		CommandBase::pDriveTrain->ArcadeDrive(xSpeed, zRotation);
	}		

	// log the test results
	if (this->isDriveTest)
	{
		LOG("[DriveWithJoystick] Target Distance: " << this->dDistance
		    		<< " Current Distance: " << CommandBase::pDriveTrain->GetLeftDistance()
				<< " Target Position: " << CommandBase::pDriveTrain->GetTargetPosition()
				<< " Current Postion: " << CommandBase::pDriveTrain->GetLeftPosition()
				<< " Velocity: " << CommandBase::pDriveTrain->GetVelocity()
				<< " Time: " << this->pTimer->Get());
	}
	else if (this->isTurnTest)
	{
		LOG("[DriveWithJoystick] Set Point: " << this->dSetpoint
				<< " Current Angle: " << CommandBase::pDriveTrain->GetAngle()
				<< " Rate: " << CommandBase::pDriveTrain->GetRotateToAngleRate()
				<< " Time: " << this->pTimer->Get());
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
