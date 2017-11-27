#include "cRobot.h"
#include <iostream>

int main()
{
//	int x;		float y;	string name;	
//	cRobot bob;
//	bob.MoveForward( 10.0f );
//	float dist = bob.getCurrentLocation();
//	std::cout << dist << " cm " << std::endl;
	
	
	
	
	
	cRobot* pHerbert = new cRobot();
	
	pHerbert->MoveForward( 10.0f );
	
	float dist = pHerbert->getCurrentLocation();
	std::cout << dist << " cm " << std::endl;
		
	// At some point
	delete pHerbert;
	
	return 0;
}





