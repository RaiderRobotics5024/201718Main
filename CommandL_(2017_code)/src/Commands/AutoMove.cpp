#include "AutoMove.h"
#include "../RobotMap.h"


AutoMove::AutoMove(double speed, double d_target, double a_target, double kP)
{
	Requires(CommandBase::pDriveTrain);

	//CommandBase::pDriveTrain->pLeftFrontMotor->SetEncPosition(0);//SetPosition(0.0);
	//CommandBase::pDriveTrain->pRightFrontMotor->SetEncPosition(0);//SetPosition(0.0);

	SmartDashboard::PutNumber("Enc", CommandBase::pDriveTrain->GetRightEncoderValue());
	this->d_target = d_target;
	this->a_target = a_target;
	this->speed = speed;
	this->kP = kP;
	this->isUltraUsed = false;
}


AutoMove::AutoMove(double speed, double d_target, double a_target, double kP, bool isUltraUsed){
	Requires(CommandBase::pDriveTrain);
	Requires(CommandBase::pBIOS);


	//CommandBase::pDriveTrain->pLeftFrontMotor->SetEncPosition(0);//SetPosition(0.0);
	//CommandBase::pDriveTrain->pRightFrontMotor->SetEncPosition(0);//SetPosition(0.0);


	this->a_target = a_target;
	this->speed = speed;
	this->kP = kP;
	this->isUltraUsed = isUltraUsed;

	if(!isUltraUsed){
		this->d_target = d_target;
	}else{
		this->d_target = d_target;
	}
}

// Called just before this Command runs the first time
void AutoMove::Initialize()
{
	//CommandBase::pDriveTrain->pLeftFrontMotor -> SetPosition(0.0);
	//CommandBase::pDriveTrain->pRightFrontMotor -> SetPosition(0.0);


}

// Called repeatedly when this Command is scheduled to run
void AutoMove::Execute()

{
}

// Make this return true when this Command no longer needs to run execute()
bool AutoMove::IsFinished()
{
	SmartDashboard::PutNumber("Enc_IsFinsihed", CommandBase::pDriveTrain->GetRightEncoderValue());

	bool isDone;
	if(!this->isUltraUsed){
		SmartDashboard::PutString("EncoderUsed", "yes");
		isDone = CommandBase::pDriveTrain->GoForward(d_target, speed, a_target, kP);
	}
	else{
		SmartDashboard::PutString("EncoderUsed", "no");
		isDone = CommandBase::pDriveTrain->GoUltraForward(d_target, speed, a_target, kP, CommandBase::pBIOS->GetUltraAt(2));
	}

	/*if(isDone){
		CommandBase::pDriveTrain->pLeftFrontMotor -> SetPosition(0.0);
		CommandBase::pDriveTrain->pRightFrontMotor -> SetPosition(0.0);
		return isDone;
	}else{
		return isDone; //return isDone anyways
	}*/
	/*if (isDone)
	{
		CommandBase::pDriveTrain->pLeftFrontMotor->SetPosition(0.0);
		CommandBase::pDriveTrain->pRightFrontMotor->SetPosition(0.0);
	}*/

	return isDone;
}

// Called once after isFinished returns true
void AutoMove::End()
{
	//CommandBase::pDriveTrain->pLeftFrontMotor->SetPosition(0.0);
	//CommandBase::pDriveTrain->pRightFrontMotor->SetPosition(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoMove::Interrupted()
{
	End();
}
