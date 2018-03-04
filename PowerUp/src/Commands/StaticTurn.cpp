#include "StaticTurn.h"

StaticTurn::StaticTurn()
{
	LOG("[StaticTurn] Constructed");

	if (CommandBase::pDriveTrain != nullptr)
		Requires(CommandBase::pDriveTrain);

	// Create a PID object with values tweaked specifically for turning
	// This allows us to have multiple PIDs working
	m_PID = new PID(PROPORTIONAL, INTEGRAL, DERIVATIVE, BUFFER_ZONE) ;

	//Creates a stopwatch for use of timing our the command if unable to reach angle
	this->timer = new Timer() ;

	this->target = 0.0 ;

	return ;
}

StaticTurn::StaticTurn(double angleDeg)
{
	LOG("[StaticTurn] Contructed with angle: "<<angleDeg);
	m_PID = new PID(PROPORTIONAL, INTEGRAL, DERIVATIVE, BUFFER_ZONE) ;
	this->target = angleDeg ;
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
	this->timer->Start() ;
	while (pDriveTrain->GetAHRS()->IsCalibrating()) ;
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

	pDriveTrain->ArcadeDrive(0, calcPID) ;

	if (iCounter++ == 10)
	{
		bool isConnected = pDriveTrain->GetAHRS()->IsConnected() ;
		bool isCal = pDriveTrain->GetAHRS()->IsCalibrating() ;
		bool isRot = pDriveTrain->GetAHRS()->IsRotating() ;

		SmartDashboard::PutNumber("yaw", yaw) ;
		SmartDashboard::PutNumber("NavX_Connected", isConnected) ;
		SmartDashboard::PutNumber("NavX_Calibrating", isCal) ;
		SmartDashboard::PutNumber("NavX_Rotating", isRot) ;
		SmartDashboard::PutNumber("PID_calcPID", calcPID) ;
		SmartDashboard::PutNumber("PID_currentTarget", m_PID->getTarget()) ;

		LOG("[StaticTurn] Current Position: " << CommandBase::pDriveTrain->GetLeftPosition() << " Target Position: " << CommandBase::pDriveTrain->GetTargetPosition());

		LOG("[StaticTurn] Time: "  << this->timer->Get());

		iCounter = 0;
	}

	return ;
}

// Make this return true when this Command no longer needs to run execute()
bool StaticTurn::IsFinished()
{
	if (m_PID->isFinished())
	{
		LOG("[StaticTurn] Finished Turn");

		return true;
	}

	if (this->timer->Get() > TIMEOUT)
	{
		LOG("[StaticTurn] Timed Out");

		return true ;
	}

	return false;
}

// Called once after isFinished returns true
void StaticTurn::End() {
	LOG("[StaticTurn] Reached target: "<<m_PID->getTarget()) ;
	delete this->m_PID ;
	delete this->timer ;
	return ;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StaticTurn::Interrupted() {
	LOG("[StaticTurn] was interupted");
}
