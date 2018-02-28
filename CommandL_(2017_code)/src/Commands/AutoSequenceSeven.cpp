#include "AutoSequenceSeven.h"
#include "Commands/Turn.h"
#include "Commands/AutoMove.h"
#include "Commands/TimedShoot.h"
#include "Commands/RetractSFM.h"
#include "Commands/ExtendSFM.h"
#include "Commands/ResetGyro.h"
#include "Commands/ResetEncoders.h"




/** Auto_7_XX - low bar ultra
 *	1. drives forward "Auto_7_Enc_D1" inches with encoders (to cross low bar)
 *	2. drives forward till "Auto_7_Ultra_D1" meters to castle wall with ultrasonic (to reach target location)
 *	3. turns 240 degrees toward the tower
 *	4. drives forward till "Auto_7_Ultra_D2" meters away from guardril with ultrasonic
 *	5. shoot high
 */

AutoSequenceSeven::AutoSequenceSeven()
{
	SmartDashboard::PutString("Auto", "AutoSequenceSeven");
	//AddSequential(new AutoMove(0.5, 1.0, 0, 1.0, true));
	double speed1 = Preferences::GetInstance()->GetFloat("Auto_7_Speed1", 0.7); //0.7 is Guinevere speed, 1.0 is Arthur speed
	double speed2 = Preferences::GetInstance()->GetFloat("Auto_7_Speed2", 0.6);// 0.6 was tested on Arthur
	double enc_target = Preferences::GetInstance()->GetFloat("Auto_7_Enc_D1", 79);
	double ultra_target = Preferences::GetInstance()->GetFloat("Auto_7_Ultra_D1", 1.0); //1 meter away from castle wall
	double enc_target2 = Preferences::GetInstance()->GetFloat("Auto_7_Enc_D2", -35); //1.5 meters away from guardrail

	double turn_target = Preferences::GetInstance()->GetFloat("Auto_7_T1", 240);
	double kP_Straight = Preferences::GetInstance()->GetDouble("Auto_Straight_kP", 1.0f);
	double kP_Turn = Preferences::GetInstance()->GetDouble("Auto_Turn_kP", 1.3f);

	AddSequential(new ResetGyro());
	AddSequential(new ResetEncoders());

	// Arm extend and initial move forward (pre ultrasound)
	AddParallel(new RetractSFM());
	AddSequential(new AutoMove(speed1, enc_target, 0, kP_Straight));

	AddSequential(new ResetEncoders());

	// Arm retract and ultrasound move to wall
	AddParallel(new ExtendSFM());
	AddSequential(new AutoMove(speed2, ultra_target, 0, kP_Straight, true));

	AddSequential(new ResetEncoders());

	// Turn to face tower
	AddSequential(new Turn(turn_target, kP_Turn));

	AddSequential(new ResetEncoders());

	// Move towards tower
	AddSequential(new AutoMove(speed1, enc_target2, turn_target, kP_Straight));

	// Shoot
	AddSequential(new TimedShoot(107));
	//double speed, double d_target, double a_target, double kP)
}
