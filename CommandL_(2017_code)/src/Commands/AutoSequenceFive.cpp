#include "AutoSequenceFive.h"
#include "Commands/AutoMove.h"


/*
 * JUST CHARRRRRRRRRRRRRRGE, nothing to be changed
 */
AutoSequenceFive::AutoSequenceFive()
{
	SmartDashboard::PutString("Auto", "AutoSequenceFive");
	//AddSequential(new AutoMove(0.5, 1.0, 0, 1.0, true));
	double distance = Preferences::GetInstance()->GetDouble("Auto_5_D1", 200.0f);
	AddSequential(new AutoMove(1.0, distance, 0, 1.0));
	//double speed, double d_target, double a_target, double kP)
}
