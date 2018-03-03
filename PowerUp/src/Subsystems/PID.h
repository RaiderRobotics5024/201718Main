#ifndef PID_H
#define PID_H

#include "SmartDashboard/SmartDashboard.h"
#include <Commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <stdio.h>
#include <string>

class PID : public frc::Subsystem {
	#define CYCLE_TIME	0.02
	double tweakP, tweakI, tweakD, buffer, err, Ierr, Derr, prevErr, target, current ;

public:
	PID(double, double, double, double) ;
	PID(std::string) ;
	void InitDefaultCommand() ;
	double calcPID(double) ;
	void zeroDistance() ;
	void zeroIntegral() ;
	bool setTarget(double) ;
	double getTarget() ;
	double getDistance() ;
	double getValue(unsigned char) ;
	bool isFinished() ;
};

#endif  // PID_H
