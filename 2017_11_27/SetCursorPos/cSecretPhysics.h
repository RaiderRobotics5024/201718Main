#ifndef _cSecretPhysics_HG_
#define _cSecretPhysics_HG_

// *****************************************
// DON'T WORRY ABOUT THIS CODE FOR THE ROBOT
// (Like this has stuff that isn't important 
//  for the specifics of the lesson)
// *****************************************

// https ://wpilib.screenstepslive.com/s/4485/m/13810/l/277232-scheduling-commands
// This is typically called on each driver station update 
//	which occurs every 20 ms or 50 times per second. 

#include "sPhysInfo.h"

class cSecretPhysics
{
public:
	cSecretPhysics();		// baseTimeStep = 0.02f (20 ms)
							// timeStepJitter = 0.005f (5 ms max)
	cSecretPhysics(float baseTimeStep, float timeStepJitter);

	// Updates the simulation
	// (using forward explicit Euler integration, if you're curious)
	// Returns: the length of this tick (in seconds)
	double UpdateTick(sPhysInfo &physState);

	double getElapsedTime(void);

	float getRandomFloat(float min, float max);
	double getRandomDouble(double min, double max);

	// These methods are "overloaded". 
	// NOTE: In C or C++ the RETURN VALUE IS IGNORED! 
	// (i.e. only the PARAMETERS make them different
	float getRand(float min, float max);
	double getRand(double min, double max);

	// This is a "templated" method, which will
	//	generate something like the methods above
	//	AT COMPILE TIME. 
	// SHORT VERSION: DON'T write this stuff for FRC Robot. There is NO NEED. Ever.
//	template <class T>
//	T getRandom(T min, T max);

private:
	double m_baseTimeStep;
	double m_timeStepJitter;
	double m_elapsedTime;

	static const double DEFAULTBASETIMESTEP;	// baseTimeStep = 0.02f (20 ms)
	static const double DEFAULTTIMESTEPJITTER;	// timeStepJitter = 0.005f (5 ms max)
};

#endif
