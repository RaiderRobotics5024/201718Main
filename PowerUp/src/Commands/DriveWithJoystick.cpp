#include "DriveWithJoystick.h"
#include "../Utilities/Log.h"
#include <math.h>
#include "../RobotMap.h"
#include "../Subsystems/DriveTrainMap.h"
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
						
			// set starting point
			this->dDistance = 0.0;
			this->dLastDistance = 0.0;
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
			CommandBase::pDriveTrain->ResetGyro();
			CommandBase::pDriveTrain->TurnSetup();
						
			// set starting angle
			this->dSetpoint = 0.0;
			this->dLastSetpoint = 0.0;
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

	// set the PID values using the POV stick
	if (pJoyDrive->GetPOV(0) > -1)
	{
		if (this->isDriveTest)
		{
			switch (pJoyDrive->GetPOV(0))
			{
				case 315: dTalon_P += 0.01; break;
				case   0: dTalon_I += 0.01; break;
				case  45: dTalon_D += 0.01; break;
				case 225: dTalon_P -= 0.01; if (dTalon_P < 0.0 ) dTalon_P = 0.0; break;
				case 180: dTalon_I -= 0.01; if (dTalon_I < 0.0 ) dTalon_I = 0.0; break;
				case 135: dTalon_D -= 0.01; if (dTalon_D < 0.0 ) dTalon_D = 0.0; break;
				default : break;
			}
			CommandBase::pDriveTrain->SetTalonPID(dTalon_P, dTalon_I, dTalon_D);
		}
		else if (this->isTurnTest)
		{
			switch (pJoyDrive->GetPOV(0))
			{
				case 315: dGyro_P += 0.01; break;
				case   0: dGyro_I += 0.01; break;
				case  45: dGyro_D += 0.01; break;
				case 225: dGyro_P -= 0.01; if (dGyro_P < 0.0 ) dGyro_P = 0.0; break;
				case 180: dGyro_I -= 0.01; if (dGyro_I < 0.0 ) dGyro_I = 0.0; break;
				case 135: dGyro_D -= 0.01; if (dGyro_D < 0.0 ) dGyro_D = 0.0; break;
				default : break;
			}
			CommandBase::pDriveTrain->SetGyroPID(dTalon_P, dTalon_I, dTalon_D);
		}
	}
		    
	// the drive/turn test will start if we are in test mode and the distance/setpoint has changed
	if (this->dLastDistance != this->dDistance || this->dLastSetpoint != this->dSetpoint)
	{
		if (this->isDriveTest)
		{
			this->pTimer->Reset();
			this->pTimer->Start();
			
			CommandBase::pDriveTrain->Drive(dDistance, 1.0);
			
			this->dLastDistance = dDistance;
			this->dLastSetpoint = dSetpoint;
		}
		else if (this->isTurnTest)
		{
			this->pTimer->Reset();
			this->pTimer->Start();
			
			CommandBase::pDriveTrain->SetSetpoint(dSetpoint);
			CommandBase::pDriveTrain->Turn();
			
			this->dLastDistance = dDistance;
			this->dLastSetpoint = dSetpoint;
		}
	}

	// drive the bot as usual if not drive test and not turn test
	if (!this->isDriveTest && !this->isTurnTest)
	{
		// Y-axis is -1 (forward) and 1 (backwards) but we need the motor
		// speed to be 1 (forward) and -1 (reverse) so multiply input by -1
		dSpeed    = pJoyDrive->GetY(XboxController::kLeftHand) * -1;
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
			<< " P : " << this->dTalon_P
			<< " I : " << this->dTalon_I
			<< " D : " << this->dTalon_D
			<< " Time: " << this->pTimer->Get());
	}
	else if (this->isTurnTest)
	{
		LOG("[DriveWithJoystick] TA: " << this->dSetpoint
			<< " CA: " << CommandBase::pDriveTrain->GetAngle()
			<< " Rate: " << CommandBase::pDriveTrain->GetRotateToAngleRate()
			<< " P : " << this->dGyro_P
			<< " I : " << this->dGyro_I
			<< " D : " << this->dGyro_D
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
		}

		if (CommandBase::pDriveTrain->GetRightPosition() >= CommandBase::pDriveTrain->GetTargetPosition() && pTimer->Get() > 0)
		{
			LOG("[DriveWithJoystick] Reached Right Target");
		}
	}
	else if (this->isTurnTest)
	{
		if (CommandBase::pDriveTrain->GetAngle() >= (this->dSetpoint - GYRO_TOLERANCE_DEGREES)
		 && CommandBase::pDriveTrain->GetAngle() <= (this->dSetpoint + GYRO_TOLERANCE_DEGREES) && pTimer->Get() > 0)
		{
			LOG("[DriveWithJoystick] Reached Turn Angle");
		}
	}

	// We want the command to run until we stop it manually
	// by toggling drive/turn test bumper
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
