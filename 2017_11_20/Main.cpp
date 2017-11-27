#include "cRobot.h"
#include "cMotor.h"
#include <iostream>

int main()
{

	cRobot* pY = new cRobot();
	pY->pLeft = new cMotor();
	pY->pRight = new cMotor();
//	int y;
//	cRobot Herbert;
//	float x = 10.0f;
//	Herbert.MoveForward(x);
//	cRobot px;	//STACK -> use "dot" operator.
//	cRobot* pHerbert = new cRobot();
	
	cRobot* pHerbert = new cRobot();
	pHerbert->MoveForward(10.0f); //HEAT based variable "arrow"

	float dist = pHerbert->getCurrentLocation();
	std::cout << dist << " cm " << std::endl;

	delete pHerbert;
	return 0;
}

