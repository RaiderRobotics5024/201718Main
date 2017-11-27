#include "cRobot.h"
#include <iostream>

cRobot::cRobot()
{
	std::cout << "A robot is made!" << std::endl;
	return;
}


cRobot::~cRobot()
{
	std::cout << "A robot dies." << std::endl;
	return;
}


void cRobot::Move(std::string direction,
		  float distance)
{
	// Remember to include iostream
	std::cout << distance << " m in "
	          << direction << std::endl;
	return;
}


void cRobot::Throw(int dist)
{
	std::cout << "Throw " << dist << std::endl;
	return;
}











