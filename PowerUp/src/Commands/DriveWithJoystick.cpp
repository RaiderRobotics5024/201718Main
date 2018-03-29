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
			CommandBase::pDriveTrain->InitAutonomousMode();
			CommandBase::pDriveTrain->DriveSetup();
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
			CommandBase::pDriveTrain->InitAutonomousMode();
			CommandBase::pDriveTrain->TurnSetup();
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
		CommandBase::pDriveTrain->ResetGyro();
	}
	else if (pJoyDrive->GetBButtonPressed())
	{
		this->dDistance = 80.0;
		this->dSetpoint = 90.0;
		CommandBase::pDriveTrain->ResetGyro();
	}
	else if (pJoyDrive->GetAButtonPressed())
	{
		this->dDistance = 170.0;
		this->dSetpoint = 180.0;
		CommandBase::pDriveTrain->ResetGyro();
	}
	else if (pJoyDrive->GetXButtonPressed())
	{
		this->dDistance = 230.0;
		this->dSetpoint = -90.0;
		CommandBase::pDriveTrain->ResetGyro();
	}

	// use start button to start the drive or turn test
	if (pJoyDrive->GetStartButtonPressed())
	{
		if (this->isDriveTest)
		{
			this->pTimer->Reset();
			this->pTimer->Start();
			
			CommandBase::pDriveTrain->Drive(dDistance, 1.0);
		}
		else if (this->isTurnTest)
		{
			this->pTimer->Reset();
			this->pTimer->Start();
			
			CommandBase::pDriveTrain->SetSetpoint(dSetpoint);
			CommandBase::pDriveTrain->Turn();
		}
	}
	
	// drive the bot as usual if not drive test and not turn test
	if (!this->isDriveTest && !this->isTurnTest)
	{
		dSpeed    = pJoyDrive->GetY(XboxController::kLeftHand) * -1; // up on stick is negative
		dRotation = pJoyDrive->GetX(XboxController::kLeftHand);

		if (fabs(dSpeed) <= XBOX_DEADZONE_LEFT_JOY)
		{
			dSpeed = 0.0;
		}

		if (fabs(dRotation) <= XBOX_DEADZONE_LEFT_JOY)
		{
			dRotation = 0.0;
		}

		CommandBase::pDriveTrain->ArcadeDrive(dSpeed, dRotation);
	}		

	// log the test results
	if (this->isDriveTest)
	{
		LOG("[DriveWithJoystick] TD: " << this->dDistance
			<< " TP: " << CommandBase::pDriveTrain->GetTargetPosition()
			<< " RD: " << CommandBase::pDriveTrain->GetRightDistance()
			<< " RP: " << CommandBase::pDriveTrain->GetRightPosition()
			<< " RE: " << CommandBase::pDriveTrain->GetRightCosedLoopError()
			<< " RV: " << CommandBase::pDriveTrain->GetRightVelocity()
			<< " LD: " << CommandBase::pDriveTrain->GetLeftDistance()
			<< " LP: " << CommandBase::pDriveTrain->GetLeftPosition()
			<< " LE: " << CommandBase::pDriveTrain->GetLeftClosedLoopError()
			<< " LV: " << CommandBase::pDriveTrain->GetLeftVelocity()
			<< " MS: " << dSpeed
			<< " RS: " << dRotation
			<< " Time: " << this->pTimer->Get());
	}
	else if (this->isTurnTest)
	{
		LOG("[DriveWithJoystick] TA: " << this->dSetpoint
				<< " CA: " << CommandBase::pDriveTrain->GetAngle()
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
	if (this->isDriveTest)
	{
		if (CommandBase::pDriveTrain->GetLeftPosition() >= CommandBase::pDriveTrain->GetTargetPosition() && pTimer->Get() > 0)
		{
			LOG("[DriveWithJoystick] Reached Left Target");
			CommandBase::pDriveTrain->ResetDrive();
			return true;
		}

		if (CommandBase::pDriveTrain->GetRightPosition() >= CommandBase::pDriveTrain->GetTargetPosition() && pTimer->Get() > 0)
		{
			LOG("[DriveWithJoystick] Reached Right Target");
			CommandBase::pDriveTrain->ResetDrive();
			return true;
		}
	}
	else if (this->isTurnTest)
	{
		if (fabs(CommandBase::pDriveTrain->GetAngle()) >= fabs(this->dSetpoint) && pTimer->Get() > 0)
		{
			LOG("[DriveWithJoystick] Reached Turn Angle");
			CommandBase::pDriveTrain->ResetDrive();
			return true;
		}
	}
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
