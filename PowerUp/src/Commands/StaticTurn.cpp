#include "StaticTurn.h"

StaticTurn::StaticTurn()
{
	LOG("[StaticTurn] Constructed\n");
	if (CommandBase::pDriveTrain != nullptr)
		Requires(CommandBase::pDriveTrain);
	// Create a PID object with values tweaked specifically for turning
	// This allows us to have multiple PIDs working
	m_pPID = new PID(PROPORTIONAL, INTEGRAL, DERIVATIVE, BUFFER_ZONE) ;
	this->m_pTimer = new Timer() ;
	//Default NULL, target is NULL if the this objects target is dynamic (not the same everytime)
	this->target = 0.0 ;
	this->yawOffset = 0.0 ;
	this->counter = 13 ;
	return ;
}

StaticTurn::StaticTurn(double angleDeg)
{
	LOG("[StaticTurn] Constructed with angle: "<<angleDeg) ;
	Requires(CommandBase::pDriveTrain) ;
	this->m_pTimer = new Timer() ;
	this->m_pPID = new PID(PROPORTIONAL, INTEGRAL, DERIVATIVE, BUFFER_ZONE) ;
	this->target = angleDeg ;
	this->yawOffset = 0.0 ;
	this->counter = 13 ;
	return ;
}

// Call before you use "StaticTurn->Start()"
void StaticTurn::setTarget(double deg)
{
	LOG("[StaticTurn::setTarget] to "<<deg) ;
	m_pPID->setTarget(deg) ;
	return ;
}

// Called just before this Command runs the first time
void StaticTurn::Initialize()
{
	LOG("[StaticTurn::Initialize] Initialized with angle "<<this->m_pPID->getTarget()<<"\n");
	this->pDriveTrain->ResetGyro() ;
	m_pPID->reset() ;
	if (m_pPID->getTarget() == 0.0) {
		LOG("[StaticTurn::Initialize] PID target is 0, replacing with StaticTurn's target") ;
		setTarget(this->target) ;
	}
	if (m_pPID->getTarget() == 0.0) {
		LOG("[StaticTurn::Initialize] Target is still 0 and will therefore cancel the command") ;
		this->Cancel() ;
	}
	this->m_pTimer->Start() ;
	return ;
}

// Called repeatedly when this Command is scheduled to run
void StaticTurn::Execute()
{
	double yaw = pDriveTrain->GetAngle() ;
	double calcPID = m_pPID->calcPID(yaw) ;

/*		v	Code for printing out PID values if debugging/tweaking is needed	v	*/
/*	if (this->counter++ >= 12)
		printf("[StaticTurn::Execute] CalcPID_%4.2f | Yaw: %+6.2f | Err: %4.2f | Ierr: %5.2f | Derr: %+3.1f | Time: %3.2f\n",
			calcPID , yaw , m_pPID->getErr() , m_pPID->getIerr() , m_pPID->getDerr() , m_pTimer->Get()) ;
*/
	CommandBase::pDriveTrain->ArcadeDrive(0, calcPID) ;
	return ;
}

// Make this return true when this Command no longer needs to run execute()
bool StaticTurn::IsFinished()
{
	if (this->m_pPID->isFinished())
	{
		LOG("[StaticTurn::IsFinished] Finished Turn");
		return true;
	}
	if (this->m_pTimer->Get() > TIMEOUT)
	{
		LOG("[StaticTurn::IsFinished] Timed Out");
		return true ;
	}
	return false;
}

// Called once after isFinished returns true
void StaticTurn::End()
{
	this->m_pPID->reset() ;
	this->m_pTimer->Stop() ;
	this->m_pTimer->Reset() ;
	this->pDriveTrain->ResetGyro() ;
	LOG("[StaticTurn::End] Reset pid,timer,gyro") ;
	return ;
}

StaticTurn::~StaticTurn()
{
	delete this->m_pPID ;
	delete this->m_pTimer ;
	LOG("[StaticTurn::End] Deleted PID and Timer") ;
	return ;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StaticTurn::Interrupted()
{
	LOG("[StaticTurn::Interrupted] Nothing will be done otherwise.") ;
	return ;
}
