#include "cRobot.h"

cRobot::cRobot()
{
	this->m_secondsElapsed = 0.0;
	this->m_currentSpeed = 0.0f;
	this->m_currentLocation =  0.0f;
	return;
}


cRobot::~cRobot()
{
	return;
}

// Can't do this on a real robot
void cRobot::MoveForward( float numCentiMeters )
{
	this->m_currentLocation += numCentiMeters;
	return;
}

void cRobot::SetForwardSpeed( float cmPerSecond )
{
	this->m_currentSpeed = cmPerSecond;
	return;
}

void cRobot::Tick( float seconds )
{
	double cmMovedThisTick = (double)seconds * this->m_currentSpeed;
	this->m_currentLocation += cmMovedThisTick;

	return;
}

float cRobot::getCurrentSpeed(void)
{
	return this->m_currentSpeed;
}

float cRobot::getCurrentLocation(void)
{
	return this->m_currentLocation;
}

