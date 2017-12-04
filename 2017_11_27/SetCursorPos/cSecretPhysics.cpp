#include "cSecretPhysics.h"
#include <stdlib.h>				// for rand()

// *****************************************
// DON'T WORRY ABOUT THIS CODE FOR THE ROBOT
// (Like this has stuff that isn't important 
//  for the specifics of the lesson)
// *****************************************

cSecretPhysics::cSecretPhysics()
{
	this->m_baseTimeStep = cSecretPhysics::DEFAULTBASETIMESTEP;		// (20 ms)
	this->m_timeStepJitter = cSecretPhysics::DEFAULTTIMESTEPJITTER; // (5 ms max)
	this->m_elapsedTime = 0.0;
	return;
}

cSecretPhysics::cSecretPhysics(float baseTimeStep, float timeStepJitter)
{
	this->m_baseTimeStep = (double)baseTimeStep;
	this->m_timeStepJitter = (double)timeStepJitter;

	return;
}

// Updates the simulation
// (using forward explicit Euler integration, if you're curious)
// Returns: the length of this tick (in seconds)
double cSecretPhysics::UpdateTick(sPhysInfo &physState)
{
	// Get random jitter for this step
	double jitterThisStep = this->getRandomDouble( -(this->m_timeStepJitter), this->m_timeStepJitter ); 

	// "jitter" (slightly adjust) the time step
	// (to mimic random 'play' in the update on the RIO)
	double timeStepAdj = this->m_baseTimeStep + jitterThisStep;

	// Update total simulation time
	this->m_elapsedTime += timeStepAdj;

	// Perform integration
	sPoint2D deltaVThisStep;
	deltaVThisStep.x = physState.accel.x * (float)timeStepAdj;
	deltaVThisStep.y = physState.accel.y * timeStepAdj;

	physState.velocity.x += deltaVThisStep.x;
	physState.velocity.y += deltaVThisStep.y;

	sPoint2D deltaPosThisStep;
	deltaPosThisStep.x = physState.velocity.x * timeStepAdj;
	deltaPosThisStep.y = physState.velocity.y * timeStepAdj;

	physState.position.x += deltaPosThisStep.x;
	physState.position.y += deltaPosThisStep.y;

	// Returns the current time step (with jitter)
	return timeStepAdj;
}

double cSecretPhysics::getElapsedTime(void)
{
	return this->m_elapsedTime;
}


//static
const double cSecretPhysics::DEFAULTBASETIMESTEP = 0.02;	//  (20 ms)

//static 
const double cSecretPhysics::DEFAULTTIMESTEPJITTER = 0.005;	// (5 ms max)

float cSecretPhysics::getRandomFloat(float min, float max)
{
	// From: https://stackoverflow.com/questions/686353/c-random-float-number-generation
	float r3 = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
	return r3;
}

double cSecretPhysics::getRandomDouble(double min, double max)
{
	// From: https://stackoverflow.com/questions/686353/c-random-float-number-generation
	double r3 = min + static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (max - min)));
	return r3;
}

//// These methods are "overloaded". 
//	// NOTE: In C or C++ the RETURN VALUE IS IGNORED! 
//	// (i.e. only the PARAMETERS make them different
float cSecretPhysics::getRand(float min, float max)
{
	// From: https://stackoverflow.com/questions/686353/c-random-float-number-generation
	float r3 = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
	return r3;
}

double cSecretPhysics::getRand(double min, double max)
{
	// From: https://stackoverflow.com/questions/686353/c-random-float-number-generation
	double r3 = min + static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (max - min)));
	return r3;
}
