#ifndef _cRobot_HG_
#define _cRobot_HG_

#include "sPoint2D.h"
#include "cMotor.h"

#include "cSecretPhysics.h"

class cRobot
{
public:
	cRobot();
	~cRobot();
	float mass;

	// This is effectively motor "force", really
	void setMotorSpeedX(float speed);
	void setMotorSpeedY(float speed);
	void setMotorSpeed(float Xspeed, float Yspeed);
	sPoint2D getCurrentMotorSpeed(void);

	sPoint2D getPosition(void);
	sPoint2D getVelocity(void);
	sPoint2D getAccel(void);

	// These are called over and over
	// (returns the frame time + jitter)
	double SimulationTimeTick(void);
	double getElapsedTime(void);
private:
	cSecretPhysics* m_pSPThingy;
	// Current state of the robot
	sPhysInfo m_physState;

	cMotor* m_pXMotor;
	cMotor* m_pYMotor;

	static const float DEFAULTROBOTMASSKG;	// 50.0kg
};



#endif 
