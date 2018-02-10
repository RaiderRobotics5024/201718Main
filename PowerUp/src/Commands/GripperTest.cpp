#include <Commands/GripperTest.h>
#include <math.h>
#include "../RobotMap.h"

/**
 *
 */

GripperTest::GripperTest()
{
	std::cout << "[Gripper Test] Constructed" << std::endl;

	if (CommandBase::pIntake != nullptr)
	{
		Requires(CommandBase::pIntake);
	}
	else
	{
		std::cout << "[Gripper Test] driveTrain is null!" << std::endl;
	}

	return;
}

/**
 *
 */

void GripperTest::Initialize()
{
	std::cout << "[GripperTest] Initialized" << std::endl;

	return;
}

/**
 *
 */

void GripperTest::Execute()
{
	double forwardSpeed = CommandBase::pOI->GetJoystickOperator()->GetY(XboxController::kLeftHand);

	if (fabs(forwardSpeed) <= XBOX_DEADZONE_LEFT_JOY)
	{
		forwardSpeed = 0.0;
	}

	CommandBase::pIntake-> SetMotorSpeed(forwardSpeed,forwardSpeed);

	return;

}

/**
 *
 */

bool GripperTest::IsFinished()
{
	return false;
}

/**
 *
 */

void GripperTest::End()
{
	return;
}

/**
 *
 */

void GripperTest::Interrupted()
{
	return;
}
