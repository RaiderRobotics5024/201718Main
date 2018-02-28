#include "AutoSequenceFour.h"
#include "Commands/Turn.h"
#include "Commands/TimedShoot.h"




/*****
 * this auto is spy bot, shoot but not move
 */
AutoSequenceFour::AutoSequenceFour()
{
	SmartDashboard::PutString("Auto", "AutoSequenceFour");
	AddSequential(new TimedShoot(104));
}
