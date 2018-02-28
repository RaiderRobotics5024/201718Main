#ifndef DriveForward_H
#define DriveForward_H

#include "../CommandBase.h"
#include "WPILib.h"

class DriveForward: public CommandBase
{
private:
	double distance;
	double driveSpeed;
	double error;
public:
	DriveForward(double dist, double maxSpeed);
	DriveForward(double dist);
	DriveForward();
	void init(double dist, double maxSpeed);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
