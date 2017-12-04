#include <iostream>
#include <Windows.h>
#include <iomanip>

#include "cRobot.h"

void MoveCursorToXY(int x, int y);
void PrintRobotState(cRobot* pRobot);
void DrawRobot(cRobot* pRobot);
void DrawTarget(double x, double y);
void DrawJitterBar(double jitter, double drawScale);


int main()
{

	double totalSimTime = 150.0f;			// 15 seconds

	cRobot* pRobby = new cRobot();

	sPoint2D target(30, 10); 

	bool bKeepSimulating = true;
	do
	{


		//pRobby->setMotorSpeed(3.0f, 2.0f);

		// **************************************
		// Don't touch this part
		// **************************************
		double frameTime = pRobby->SimulationTimeTick();
		// Done? 
		if (pRobby->getElapsedTime() >= totalSimTime)
		{
			bKeepSimulating = false;
		}
		PrintRobotState(pRobby);
		DrawRobot(pRobby);
		DrawTarget(target.x, target.y);
		DrawJitterBar(frameTime, 500.0);
		Sleep(20);
		// **************************************
	} while (bKeepSimulating);


	delete pRobby;

	return 0;
}



void PrintRobotState(cRobot* pRobot)
{
	MoveCursorToXY(0, 0);
	std::cout << std::setprecision(2) << std::fixed
		<< "pos: "
		<< pRobot->getPosition().x << ", "
		<< pRobot->getPosition().y << "  ";
	MoveCursorToXY(0, 1);
	std::cout << std::setprecision(2) << std::fixed
		<< "vel: "
		<< pRobot->getVelocity().x << ", "
		<< pRobot->getVelocity().y << "  ";
	MoveCursorToXY(0, 2);
	std::cout << pRobot->getElapsedTime() << " seconds";


	return;
}

sPoint2D oldRobotPosition;

void DrawRobot(cRobot* pRobot)
{
	MoveCursorToXY( (int)oldRobotPosition.x, (int)oldRobotPosition.y);
	std::cout << " ";

	MoveCursorToXY( (int)pRobot->getPosition().x, (int)pRobot->getPosition().y);
	std::cout << "O";

	oldRobotPosition = pRobot->getPosition();

	return;
}

void DrawTarget(double x, double y)
{
	MoveCursorToXY( (int)x, (int)y );
	std::cout << "X";
	return;
}

void DrawJitterBar(double jitter, double drawScale)
{
	MoveCursorToXY(0, 3);
	std::cout << "|--------------------";

	int jitLocation = (int)(jitter * drawScale);
	MoveCursorToXY(jitLocation, 3);
	std::cout << "H";

	return;
}




// Cursor things
void MoveCursorToXY(int x, int y)
{
	COORD pos = { (SHORT)x, (SHORT)y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
	return;
}