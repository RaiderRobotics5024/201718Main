#ifndef _cMotor_HG_
#define _cMotor_HG_

// *****************************************
// DON'T WORRY ABOUT THIS CODE FOR THE ROBOT
// (Like this has stuff that isn't important 
//  for the specifics of the lesson)
// *****************************************

// This represents the state of the electric motor

class cMotor
{
public:
	cMotor();
	cMotor( double acceleration );
	void setTargetSpeed(double speed);
	double getCurrentSpeed(void);
	void SimulationTimeTick(double deltaTime, double mass);
public:

	double m_targetSpeed;
	double m_accelPerSecond;	
	static const double DEFAULT_ACCEL_PER_SECOND;		// // default is 0 to 100 in 500 ms

	double m_currentSpeed;
};

#endif
