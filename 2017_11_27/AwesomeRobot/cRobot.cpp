#include "cRobot.h"

cRobot::cRobot()
{
	this->m_pSPThingy = new cSecretPhysics();
	this->mass = cRobot::DEFAULTROBOTMASSKG;	// 50.0kg

	this->m_pXMotor = new cMotor();
	this->m_pYMotor = new cMotor();

	this->m_physState.position.x = 0.0f;
	this->m_physState.position.y = 20.0f;

//	this->m_physState.velocity.x = 1.0;
//	this->m_physState.velocity.y = 1.5;
	return;
}

cRobot::~cRobot()
{
	delete this->m_pSPThingy;
	return;
}

double cRobot::SimulationTimeTick(void)
{
	// Update through the integrator
	// (And get the current time tick, with jitter)
	double currentTickTime = this->m_pSPThingy->UpdateTick(this->m_physState);

	// Accelerate the motors
	this->m_pXMotor->SimulationTimeTick(currentTickTime, this->mass);
	this->m_pYMotor->SimulationTimeTick(currentTickTime, this->mass);

	// Adjust the velocity of the robot based on motor speed
	this->m_physState.velocity.x = this->m_pXMotor->getCurrentSpeed();
	this->m_physState.velocity.y = this->m_pYMotor->getCurrentSpeed();

	return currentTickTime;
}

// This is effectively motor "force", really
void cRobot::setMotorSpeedX(float speed)
{
	this->m_pXMotor->setTargetSpeed(speed);
	return;
}

void cRobot::setMotorSpeedY(float speed)
{
	this->m_pYMotor->setTargetSpeed(speed);
	return;
}

void cRobot::setMotorSpeed(float Xspeed, float Yspeed)
{
	this->m_pXMotor->setTargetSpeed(Xspeed);
	this->m_pYMotor->setTargetSpeed(Yspeed);
	return;
}


sPoint2D cRobot::getCurrentMotorSpeed(void)
{
	sPoint2D curSpeed;
	curSpeed.x = this->m_pXMotor->getCurrentSpeed();
	curSpeed.y = this->m_pYMotor->getCurrentSpeed();
	return curSpeed;
}


sPoint2D cRobot::getPosition(void)
{
	return this->m_physState.position;
}

sPoint2D cRobot::getVelocity(void)
{
	return this->m_physState.velocity;
}

sPoint2D cRobot::getAccel(void)
{
	return this->m_physState.accel;
}

double cRobot::getElapsedTime(void)
{
	return this->m_pSPThingy->getElapsedTime();
}


//static 
const float cRobot::DEFAULTROBOTMASSKG = 50.0f;		// 50kg
