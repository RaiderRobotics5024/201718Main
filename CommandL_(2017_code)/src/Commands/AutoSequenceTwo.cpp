#include "AutoSequenceTwo.h"
#include "Commands/Turn.h"
#include "Commands/AutoMove.h"
#include "Commands/TimedShoot.h"
#include "Commands/RetractSFM.h"
#include "Commands/ExtendSFM.h"
#include "Commands/ResetGyro.h"


/** Auto_2_XX - low bar - the encoders feedback\
 * (the pnumetics arm is ignored in the documentation, but we still love you <3 <3 <3)
 *
 *	1. drives forward "Auto_2_D1" inches with encoders (to cross low bar)
 *	2. turns Auto_2_T1 degrees, should be facing away from the tower
 *	3. drives backward  "Auto_2_D2"inches with encoders
 *	4. turns Auto_2_T2 degrees, should be facing toward the tower
 *	5. shoot high
 */

AutoSequenceTwo::AutoSequenceTwo()
{
	SmartDashboard::PutString("Auto", "AutoSequenceTwo");

	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.

	double distance1 = Preferences::GetInstance()->GetDouble("Auto_2_D1", 200.0f);
	double distance2= Preferences::GetInstance()->GetDouble("Auto_2_D2", 200.0f);
	SmartDashboard::PutNumber("Auto", distance1);
	double turn1 = Preferences::GetInstance()->GetDouble("Auto_2_T1", 45.0f);
	double turn2 = Preferences::GetInstance()->GetDouble("Auto_2_T2", 225.0f);
	double kP_Straight = Preferences::GetInstance()->GetDouble("Auto_Straight__kP", 1.0f);
	double kP_Turn = Preferences::GetInstance()->GetDouble("Auto_Turn__kP", 1.3f);

	AddSequential(new ResetGyro());
	AddSequential(new RetractSFM());
	AddSequential(new AutoMove(0.7, distance1, 0, kP_Straight));
	AddSequential(new ExtendSFM());
	AddSequential(new Turn(turn1, kP_Turn)); //turn to 45 ////////////////// kP should NEVER below 1.0 it prevents overshooting
	SmartDashboard::PutNumber("Turn", turn1);
	AddSequential(new AutoMove(0.8, distance2, turn1, kP_Straight));
	AddSequential(new Turn(turn2, kP_Turn)); //turn to 45 ////////////////// kP should NEVER below 1.0 it prevents overshooting
	AddSequential(new TimedShoot(102));

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
