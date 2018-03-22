#include "DriveWithJoystick.h"
#include "../Utilities/Log.h"
#include <math.h>
#include "../RobotMap.h"

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

	this->pStaticTurn = new StaticTurn(180.0) ;

	return;
}

/**
 *
 */
DriveWithJoystick::~DriveWithJoystick()
{
	LOG("[DriveWithJoystick] Destroyed");

	delete this->pStaticTurn ;

	return;
}

/**
 *
 */
void DriveWithJoystick::Initialize()
{
	LOG("[DriveWithJoystick] Initialized");
	this->isReverse = true;

	return;
}

/**
 *
 */
void DriveWithJoystick::Execute()
{
	frc::XboxController* pJoyDrive = CommandBase::pOI->GetJoystickDrive();

	if (pJoyDrive->GetXButtonReleased())
	{
		this->isReverse = !this->isReverse;
	}

	if (pJoyDrive->GetYButtonReleased())
	{
		LOG("[DWJ::Execute] Y button pressed")
		if (!pStaticTurn->IsRunning())
		{
			LOG("[DWJ::Execute] Starting 180deg turn")
			pStaticTurn->Start();
		}
		else
		{
			LOG("[DWJ::Execute] Canceling turn") ;
			pStaticTurn->Cancel();
		}
	}

	double xSpeed    = pJoyDrive->GetY(XboxController::kLeftHand);
	double zRotation = pJoyDrive->GetX(XboxController::kLeftHand);

	double dSlow = (pJoyDrive->GetBumper(XboxController::kRightHand)) ? 0.5 : 1;
	double dReverse = (this->isReverse) ? -1 : 1;

	if (fabs(xSpeed) <= XBOX_DEADZONE_LEFT_JOY)
	{
		xSpeed = 0.0;
	}

	if (fabs(zRotation) <= XBOX_DEADZONE_LEFT_JOY)
	{
		zRotation = 0.0;
	}

//	CommandBase::pDriveTrain->ArcadeDrive(xSpeed, zRotation);
	CommandBase::pDriveTrain->ArcadeDrive((xSpeed * dSlow * dReverse), (zRotation  * dSlow));

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
