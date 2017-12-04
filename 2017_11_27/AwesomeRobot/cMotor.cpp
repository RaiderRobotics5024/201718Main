#include "cMotor.h"

cMotor::cMotor()
{
	this->m_accelPerSecond = cMotor::DEFAULT_ACCEL_PER_SECOND;
	this->m_currentSpeed = 0.0;
	this->m_targetSpeed = 0.0;
	return;
}

cMotor::cMotor(double acceleration)
{
	this->m_accelPerSecond = acceleration;
	this->m_currentSpeed = 0.0;
	this->m_targetSpeed = 0.0;
	return;
}

void cMotor::setTargetSpeed(double speed)
{
	this->m_targetSpeed = speed;
	return;
}

double cMotor::getCurrentSpeed(void)
{
	return this->m_currentSpeed;
}

void cMotor::SimulationTimeTick(double deltaTime, double mass)
{
	//// If speed is zero, then skip
	//if ((this->m_targetSpeed <= 0.0) &&
	//	(this->m_currentSpeed <= 0.0))
	//{
	//	return;
	//}

	// HACK: speed change based on max accel over mass
	// F = m a
	// a = m DIV F
	double maxAccel = mass / this->m_accelPerSecond;

	// calc delta speed
	double maxChangeThisStep = deltaTime * maxAccel;

	if (this->m_currentSpeed < this->m_targetSpeed)
	{
		this->m_currentSpeed += maxChangeThisStep;
	}
	if (this->m_currentSpeed > this->m_targetSpeed)
	{
		this->m_currentSpeed -= maxChangeThisStep;
	}
	return;
}


//static 
const double cMotor::DEFAULT_ACCEL_PER_SECOND = 100 / 0.5;	//  0 to 100 in 500 ms
