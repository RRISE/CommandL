#include "AutoSequenceFive.h"
#include "Commands/AutoMove.h"



AutoSequenceFive::AutoSequenceFive()
{
	SmartDashboard::PutString("Auto", "AutoSequenceFive");
	AddSequential(new AutoMove(0.5, 1.0, 0, 1.0, true));
	//AddSequential(new AutoMove(1.0, 190, 0, 1.0));
	//double speed, double d_target, double a_target, double kP)
}
