#include "StaticTurn.h"
#include "../Utilities/Log.h"

StaticTurn::StaticTurn()
{
	LOG("[StaticTurn] Constructed");

	if (CommandBase::pDriveTrain != nullptr)
		Requires(CommandBase::pDriveTrain);

	// Create a PID object with values tweaked specifically for turning
	// This allows us to have multiple PIDs working
	m_PID = new PID(PROPORTIONAL, INTEGRAL, DERIVATIVE, BUFFER_ZONE) ;

	return ;
}

StaticTurn::StaticTurn(double angleDeg)
{
	LOG("[StaticTurn] Contructed with angle: "<<angleDeg);
	m_PID = new PID(PROPORTIONAL, INTEGRAL, DERIVATIVE, BUFFER_ZONE) ;
	setTarget(angleDeg) ;
	if (CommandBase::pDriveTrain != nullptr)
		Requires(CommandBase::pDriveTrain) ;
	return ;
}

// Call before you use "StaticTurn->Start()"
double StaticTurn::setTarget(double deg)
{
	double prevTarget = this->m_PID->getTarget() ;
	LOG("[StaticTurn] Set target from "<<prevTarget<<" to "<<deg);
	m_PID->setTarget(deg) ;
	if (prevTarget != 0.0)
		return prevTarget ;
	return 0.0 ;
}

// Called just before this Command runs the first time
void StaticTurn::Initialize() {
	while (pDriveTrain->GetAHRS()->IsCalibrating())
	LOG("[StaticTurn] Initialized");
	pDriveTrain->GetAHRS()->Reset() ;
	pDriveTrain->GetAHRS()->ZeroYaw() ;
	m_PID->zeroDistance() ;
	return ;
}

// Called repeatedly when this Command is scheduled to run
void StaticTurn::Execute()
{
	double yaw = pDriveTrain->GetAHRS()->GetYaw() ;
	double calcPID = m_PID->calcPID(yaw) ;
	SmartDashboard::PutNumber("yaw", yaw) ;

	bool isConnected = pDriveTrain->GetAHRS()->IsConnected() ;
	bool isCal = pDriveTrain->GetAHRS()->IsCalibrating() ;
	bool isRot = pDriveTrain->GetAHRS()->IsRotating() ;
	pDriveTrain->ArcadeDrive(0, calcPID) ;
	SmartDashboard::PutNumber("Connected", isConnected) ;
	SmartDashboard::PutNumber("Calibrating", isCal) ;
	SmartDashboard::PutNumber("Rotating", isRot) ;
	SmartDashboard::PutNumber("calcPID", calcPID) ;

	double target = m_PID->getTarget() ;
	SmartDashboard::PutNumber("currentTarget", target) ;

	IsFinished() ;

	return ;
}

// Make this return true when this Command no longer needs to run execute()
bool StaticTurn::IsFinished() {
	if (m_PID->isFinished())
		return true ;
	return false;
}

// Called once after isFinished returns true
void StaticTurn::End() {
	printf("Reached target: %f", m_PID->getTarget()) ;
	delete this->m_PID ;
	return ;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StaticTurn::Interrupted() {
	LOG("[StaticTurn] was interupted");
}
