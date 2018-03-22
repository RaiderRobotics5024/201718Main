#include "PID.h"

PID::PID(double P, double I, double D, double BZ) : frc::Subsystem("PID")
{
	LOG("[PID] Constructed with PIDB params: "<<P<<" | "<<I<<" | "<<D<<" | "<<BZ) ;
	this->tweakP = P ;
	this->tweakI = I ;
	this->tweakD = D ;
	this->buffer = BZ;
	this->err 	= 0.0 ;
	this->Ierr 	= 0.0 ;
	this->Derr 	= 0.0 ;
	this->prevErr 	= 0.0 ;
	this->target 	= 0.0 ;
	this->current 	= 0.0 ;
	return ;
}
void PID::InitDefaultCommand()
{
	//Nee
}
double PID::calcPID(double current)
{
	this->current = current ;

	//Calculate err
	this->prevErr = this->err ;
	this->err = (this->target - this->current) ;// Error = Target - Actual

	//Calculate Ierr
	// Integral is increased by the error*time (which is .02 seconds using normal IterativeRobot)
	this->Ierr += (this->err * CYCLE_TIME) ;

	// speed = distance traveled / time
	this->Derr = ((this->err - this->prevErr) / CYCLE_TIME) ;

	double pid = this->tweakP * this->err + this->tweakI * this->Ierr + this->tweakD * this->Derr ;

	if (fabs(pid) > 2.0) {
		LOG("[PID::calcPID] Calculation ("<<pid<<"), greater than 1.0, returning 0.0") ;
		return 0.0 ;
	}
	return pid ;
}
void PID::reset()
{
	this->current = 0.0 ;
	this->target = 0.0 ;
	this->err = 0.0 ;
	this->prevErr = 0.0 ;
	this->Ierr = 0.0 ;
	this->Derr = 0.0 ;
	return ;
}
void PID::zeroDistance()
{
	this->current = 0.0 ;
	return ;
}
void PID::zeroIntegral()
{
	this->Ierr = 0.0 ;
}
void PID::setTarget(double target)
{
		this->target = target;
		return ;
}
/********************************************************
 * 			GETTERS				*
 *******************************************************/
double PID::getDistance()	{ return this->current ;}
double PID::getTarget()		{ return this->target ;	}
double PID::getP()		{ return this->tweakP ;	}
double PID::getI()		{ return this->tweakI ;	}
double PID::getD()		{ return this->tweakD ;	}
double PID::getBuffer()		{ return this->buffer ;	}
double PID::getErr()		{ return this->err ;	}
double PID::getIerr()		{ return this->Ierr ;	}
double PID::getDerr()		{ return this->Derr ;	}
double PID::getPrevErr()	{ return this->prevErr ;}
/********************************************************
 *******************************************************/

bool PID::isFinished()
{
	if( abs(this->err) < this->buffer) {
		LOG("[PID::isFinished] True, at angle:"<<this->current) ;
		return true ;
	}
	return false ;
}
