#include "PID.h"

PID::PID(double P, double I, double D, double BZ) : Subsystem("PID")
{
	this->tweakP = P ;
	frc::SmartDashboard::PutNumber("DB/String 0", P) ;
	this->tweakI = I ;
	frc::SmartDashboard::PutNumber("DB/String 1", I) ;
	this->tweakD = D ;
	frc::SmartDashboard::PutNumber("DB/String 2", D) ;
	this->buffer = BZ ;
	frc::SmartDashboard::PutNumber("DB/String 3", BZ) ;
	frc::SmartDashboard::PutString("DB/String 4", "^ P, I, D, and Buffer ^") ;

	this->err = 0.0 ;
	this->Ierr = 0.0 ;
	this->Derr = 0.0 ;
	this->prevErr = 0.0 ;
	this->target = 0.0 ;
	this->current = 0.0 ;

	return ;
}

void PID::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

double PID::calcPID(double current)
{
	this->tweakP = frc::SmartDashboard::GetNumber("DB/String 0", 0.0) ;
	this->tweakI = frc::SmartDashboard::GetNumber("DB/String 1", 0.0) ;
	this->tweakD = frc::SmartDashboard::GetNumber("DB/String 2", 0.0) ;
	this->buffer = frc::SmartDashboard::GetNumber("DB/String 3", 0.0) ;

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

	printf("PID: %-5.5f | Current: %-5.2f | Err: %-5.2f | Integral: %-5.2f | Derivative: %-5.2f \n",
			pid, this->current, this->err, this->Ierr, this->Derr) ;

	if (abs(pid) > 1.0)
		return 0.0 ;
	return pid ;
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

bool PID::setTarget(double target)
{
	if (this->target != 0)
	{
		this->target = target;
		return true ;
	}
	this->target = target ;
	return false ;
}

double PID::getTarget()
{
	return this->target ;
}

double PID::getDistance()
{
	return this->current ;
}

/* Returns one of the following depending on the param,
 * or returns -1 on out_of_range param
 *
 * P tweak	-	0
 * I tweak	-	1
 * D tweak	-	2
 * buffer	-	3
 * err		-	4
 * Ierr		-	5
 * Derr		-	6
 * prevErr	-	7
 */
double PID::getValue(unsigned char n)
{
	switch (n)
	{
		case 0 :	return this->tweakP ;
		case 1 :	return this->tweakI ;
		case 2 :	return this->tweakD ;
		case 3 :	return this->buffer ;
		case 4 :	return this->err ;
		case 5 :	return this->Ierr ;
		case 6 :	return this->Derr ;
		case 7 :	return this->prevErr ;
		default:	return -1.0 ;
	}
}

bool PID::isFinished()
{
	if( abs(this->err) < this->buffer)
		return true ;
	return false ;
}
