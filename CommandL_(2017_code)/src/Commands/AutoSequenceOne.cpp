#include "AutoSequenceOne.h"
#include "Commands/Turn.h"
#include "Commands/AutoMove.h"
#include "Commands/TimedShoot.h"
#include "Commands/ExtendSFM.h"




/*****
 * this auto is spy bot
 * usually not used
 * don't use until you talk to the programmers
 * (well I guess if you are looking at this, then you are a programmer...... whatever)
 */
AutoSequenceOne::AutoSequenceOne()
{
	SmartDashboard::PutString("Auto", "AutoSequenceOne");


	double distance1 = Preferences::GetInstance()->GetDouble("Auto_1_D1", 200.0f);
	double distance2 = Preferences::GetInstance()->GetDouble("Auto_1_D2", 200.0f);

	double kP_Straight = Preferences::GetInstance()->GetDouble("Auto_Straight_kP", 1.0f);
	double kP_Turn = Preferences::GetInstance()->GetDouble("Auto_Turn_kP", 1.3f);

	AddSequential(new TimedShoot(101));
	AddSequential(new Turn(0, kP_Turn)); //turn to 0 ////////////////// kP should NEVER below 1.0 it prevents overshooting
	AddSequential(new AutoMove(0.6, distance1, 0, kP_Straight)); //turn to 0
	//AddSequential(new Turn(180, kP_Turn)); //turn to 0
	AddSequential(new AutoMove(0.6, distance2, 180, kP_Straight)); //turn to 0

	//AddSequential(new AutoMove());

	// To run multiple commands at the same time,
	// use AddParallel()
	// e.g. AddParallel(new Command1());
	//      AddSequential(new Command2());
	// Command1 and Command2 will run in parallel.

	// A command group will require all of the subsystems that each member
	// would require.
	// e.g. if Command1 requires chassis, and Command2 requires arm,
	// a CommandGroup containing them would require both the chassis and the
	// arm.
}
