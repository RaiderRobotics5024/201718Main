#ifndef CROBOT_H_
#define CROBOT_H_

#include <string>

class cRobot
{
public:
	cRobot();				// constructor
	~cRobot();				// destructor
	void Move(std::string direction,
			  float distance);
	
	void Throw(int dist);
	
};
		
#endif  /*CROBOT_H_*/
