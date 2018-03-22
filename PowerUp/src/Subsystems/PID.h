#ifndef PID_H
#define PID_H

#include <Commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <WPILib.h>
#include "../CommandBase.h"
#include "../Utilities/Log.h"

class PID : public frc::Subsystem
{
	#define CYCLE_TIME	0.02
	double tweakP, tweakI, tweakD, buffer, err, Ierr, Derr, prevErr, target, current ;

public:
	PID() ;
	PID(double, double, double, double) ;
	void InitDefaultCommand() ;
	double calcPID(double) ;
	void reset() ;
	void zeroDistance() ;
	void zeroIntegral() ;
	void setTarget(double) ;

	// Getters
	double getDistance() ;
	double getTarget() ;
	double getP() ;
	double getI() ;
	double getD() ;
	double getBuffer() ;
	double getErr() ;
	double getIerr() ;
	double getDerr() ;
	double getPrevErr() ;
	//

	bool isFinished() ;
};

#endif  // PID_H
