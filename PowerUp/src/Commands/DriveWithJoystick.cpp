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

	delete this->pJoyDrive;
	delete this->pTimer;

	return;
}

/**
 *
 */
void DriveWithJoystick::Initialize()
{
	LOG("[DriveWithJoystick] Initialized");

	this->pJoyDrive = CommandBase::pOI->GetJoystickDrive();

	CommandBase::pDriveTrain->SetTalonPID(dTalon_P, dTalon_I, dTalon_D);
	CommandBase::pDriveTrain->SetGyroPID(dGyro_P, dGyro_I, dGyro_D);

	return;
}

/**
 *
 */
void DriveWithJoystick::Execute()
{
	// use right bumper to turn on/off drive test
	if (this->pJoyDrive->GetBumperPressed(XboxController::kRightHand))
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

			DriveWithJoystick::TraceTalon();
		}
		else
		{
			CommandBase::pDriveTrain->ResetDrive();
		}
	}

	// use left bumper to turn on/off turn test
	if (this->pJoyDrive->GetBumperPressed(XboxController::kLeftHand))
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

			DriveWithJoystick::TraceGyro();
		}
		else
		{
			CommandBase::pDriveTrain->ResetDrive();
		}
	}

	// Increment PID values
	if (this->pJoyDrive->GetStickButton(XboxController::kLeftHand))
	{
		if (this->pJoyDrive->GetXButtonPressed())
		{
			if (this->isDriveTest)
			{
				this->dTalon_P += 0.0005;
				CommandBase::pDriveTrain->SetTalonPID(dTalon_P, dTalon_I, dTalon_D);
				DriveWithJoystick::TraceTalon();
			}
			else if (this->isTurnTest)
			{
				this->dGyro_P += 0.0005;
				CommandBase::pDriveTrain->SetGyroPID(dGyro_P, dGyro_I, dGyro_D);
				DriveWithJoystick::TraceGyro();
			}
		}
		else if (this->pJoyDrive->GetYButtonPressed())
		{
			if (this->isDriveTest)
			{
				this->dTalon_I += 0.0001;
				CommandBase::pDriveTrain->SetTalonPID(dTalon_P, dTalon_I, dTalon_D);
				DriveWithJoystick::TraceTalon();
			}
			else if (this->isTurnTest)
			{
				this->dGyro_I += 0.0001;
				CommandBase::pDriveTrain->SetGyroPID(dGyro_P, dGyro_I, dGyro_D);
				DriveWithJoystick::TraceGyro();
			}
		}
		else if (this->pJoyDrive->GetBButtonPressed())
		{
			if (this->isDriveTest)
			{
				this->dTalon_D += 0.001;
				CommandBase::pDriveTrain->SetTalonPID(dTalon_P, dTalon_I, dTalon_D);
				DriveWithJoystick::TraceTalon();
			}
			else if (this->isTurnTest)
			{
				this->dGyro_D += 0.001;
				CommandBase::pDriveTrain->SetGyroPID(dGyro_P, dGyro_I, dGyro_D);
				DriveWithJoystick::TraceGyro();
			}
		}
	}

	// Decrement PID values
	if (this->pJoyDrive->GetStickButton(XboxController::kRightHand))
	{
		if (this->pJoyDrive->GetXButtonPressed())
		{
			if (this->isDriveTest)
			{
				this->dTalon_P -= 0.0005;
				if (this->dTalon_P < 0.0) dTalon_P = 0.0;

				CommandBase::pDriveTrain->SetTalonPID(dTalon_P, dTalon_I, dTalon_D);
				DriveWithJoystick::TraceTalon();
			}
			else if (this->isTurnTest)
			{
				this->dGyro_P -= 0.0005;
				if (this->dGyro_P < 0.0) dTalon_P = 0.0;

				CommandBase::pDriveTrain->SetGyroPID(dGyro_P, dGyro_I, dGyro_D);
				DriveWithJoystick::TraceGyro();
			}
		}
		else if (this->pJoyDrive->GetYButtonPressed())
		{
			if (this->isDriveTest)
			{
				this->dTalon_I -= 0.0001;
				if (this->dTalon_I < 0.0) dTalon_I = 0.0;

				CommandBase::pDriveTrain->SetTalonPID(dTalon_P, dTalon_I, dTalon_D);
				DriveWithJoystick::TraceTalon();
			}
			else if (this->isTurnTest)
			{
				this->dGyro_I -= 0.0001;
				if (this->dGyro_I < 0.0) dGyro_I = 0.0;

				CommandBase::pDriveTrain->SetGyroPID(dGyro_P, dGyro_I, dGyro_D);
				DriveWithJoystick::TraceGyro();
			}

		}
		else if (this->pJoyDrive->GetBButtonPressed())
		{
			if (this->isDriveTest)
			{
				this->dTalon_D -= 0.001;
				if (this->dTalon_D < 0.0) dTalon_D = 0.0;

				CommandBase::pDriveTrain->SetTalonPID(dTalon_P, dTalon_I, dTalon_D);
				DriveWithJoystick::TraceTalon();
			}
			else if (this->isTurnTest)
			{
				this->dGyro_D -= 0.001;
				if (this->dGyro_D < 0.0) dGyro_D = 0.0;

				CommandBase::pDriveTrain->SetGyroPID(dGyro_P, dGyro_I, dGyro_D);
				DriveWithJoystick::TraceGyro();
			}
		}
	}

	// Y, B, A, X buttons set test distances and angles
	if (this->pJoyDrive->GetYButtonPressed())
	{
		this->dDistance = 18.85;
		this->dSetpoint =  0.0;
	}
	else if (this->pJoyDrive->GetBButtonPressed())
	{
		this->dDistance = 80.0;
		this->dSetpoint = 45.0;
	}
	else if (this->pJoyDrive->GetAButtonPressed())
	{
		this->dDistance = 127.0;
		this->dSetpoint =  90.0;
	}
	else if (this->pJoyDrive->GetXButtonPressed())
	{
		this->dDistance = 230.0;
		this->dSetpoint = 180.0;
	}
		    
	// the drive/turn test will start if we are in test mode and the distance/setpoint has changed
	if (this->dLastDistance != this->dDistance || this->dLastSetpoint != this->dSetpoint)
	{
		if (this->isDriveTest)
		{
			this->pTimer->Reset();
			this->pTimer->Start();
			
			CommandBase::pDriveTrain->SetTalonPID(dTalon_P, dTalon_I, dTalon_D);
			CommandBase::pDriveTrain->Drive(dDistance, 1.0);
			
			this->dLastDistance = dDistance;
			this->dLastSetpoint = dSetpoint;
		}
		else if (this->isTurnTest)
		{
			this->pTimer->Reset();
			this->pTimer->Start();
			
			CommandBase::pDriveTrain->SetGyroPID(dGyro_P, dGyro_I, dGyro_D);
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

	return;
}

/**
 *
 */
bool DriveWithJoystick::IsFinished()
{
	if (iCounter += 10)
	{
		DriveWithJoystick::Trace();

		iCounter = 0;
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

/**
 *
 */
void DriveWithJoystick::Trace()
{
	if (this->isDriveTest)
	{
		if (fabs(this->dDistance - CommandBase::pDriveTrain->GetLeftDistance()) > 1.0 && pTimer->Get() > 0)
		{
			DriveWithJoystick::TraceTalon();
		}
	}
	else if (this->isTurnTest)
	{
		DriveWithJoystick::TraceGyro();
	}
	else if (CommandBase::pDriveTrain->GetVelocity() > 0.0)
	{
		DriveWithJoystick::TraceDrive();
	}

	return;
}

/**
 *
 */
void DriveWithJoystick::TraceDrive()
{
	LOG("[DriveWithJoystick] "
		<< " SP: " << dSpeed
		<< " RT: " << dRotation
		<< " AC: " << CommandBase::pDriveTrain->GetAcceleration()
		<< " VL: " << CommandBase::pDriveTrain->GetVelocity());

	return;
}

/**
 *
 */
void DriveWithJoystick::TraceGyro()
{
	LOG("[DriveWithJoystick] TA: " << this->dSetpoint
		<< " CA: " << CommandBase::pDriveTrain->GetAngle()
		<< " Rate: " << CommandBase::pDriveTrain->GetRotateToAngleRate()
		<< " P : " << CommandBase::pDriveTrain->GetController()->GetP()
		<< " I : " << CommandBase::pDriveTrain->GetController()->GetI()
		<< " D : " << CommandBase::pDriveTrain->GetController()->GetD()
		<< " Time: " << this->pTimer->Get());

	return;
}

/**
 *
 */
void DriveWithJoystick::TraceTalon()
{
	LOG("[DriveWithJoystick] TD: " << this->dDistance
	//				<< " TP: " << CommandBase::pDriveTrain->GetTargetPosition()
	//				<< " RD: " << CommandBase::pDriveTrain->GetRightDistance()
	//				<< " RP: " << CommandBase::pDriveTrain->GetRightPosition()
	//				<< " RE: " << CommandBase::pDriveTrain->GetRightCosedLoopError()
	//				<< " RV: " << CommandBase::pDriveTrain->GetRightVelocity()
		<< " LD: " << CommandBase::pDriveTrain->GetLeftDistance()
	//				<< " LP: " << CommandBase::pDriveTrain->GetLeftPosition()
		<< " LE: " << CommandBase::pDriveTrain->GetLeftClosedLoopError()
		<< " LV: " << CommandBase::pDriveTrain->GetLeftVelocity()
		<< " MS: " << dSpeed
		<< " RS: " << dRotation
		<< " P : " << this->dTalon_P
		<< " I : " << this->dTalon_I
		<< " D : " << this->dTalon_D
		<< " AC: " << CommandBase::pDriveTrain->GetAcceleration()
		<< " VL: " << CommandBase::pDriveTrain->GetVelocity()
		<< " Time: " << this->pTimer->Get());

	return;
}
