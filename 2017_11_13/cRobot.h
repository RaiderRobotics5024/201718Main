#ifndef _cRobot_HG_
#define _cRobot_HG_

class cRobot
{
public:
	cRobot();
	~cRobot();

	// Can't do this on a real robot
	void MoveForward( float numCentiMeters );

	void SetForwardSpeed( float cmPerSecond );
	void Tick( float seconds );

	float getCurrentSpeed(void);
	float getCurrentLocation(void);

private:
	double m_secondsElapsed;
	float m_currentSpeed;
	float m_currentLocation;
};

#endif // cRobot
