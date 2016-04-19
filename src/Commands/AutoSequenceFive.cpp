#include "AutoSequenceFive.h"
#include "Commands/AutoMove.h"




/*****
 * this auto is spy bot, shoot but not move
 */
AutoSequenceFive::AutoSequenceFive()
{
	SmartDashboard::PutString("Auto", "AutoSequenceFive");
	AddSequential(new AutoMove(1.0, 190, 0, 1.0));
	//double speed, double d_target, double a_target, double kP)
}
