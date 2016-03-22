#include "AutoSequenceTwo.h"
#include "Commands/Turn.h"
#include "Commands/AutoMove.h"
#include "Commands/TimedShoot.h"



/*****
 * this auto is neutral bot
 */
AutoSequenceTwo::AutoSequenceTwo()
{
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.

	double distance1 = Preferences::GetInstance()->GetDouble("Auto_2_D1", 200.0f);
	SmartDashboard::PutNumber("Auto", distance1);
	double turn1 = Preferences::GetInstance()->GetDouble("Auto_2_T1", 45.0f);
	double kP_Straight = Preferences::GetInstance()->GetDouble("Auto_Straight__kP", 1.0f);
	double kP_Turn = Preferences::GetInstance()->GetDouble("Auto_Turn__kP", 1.3f);

	AddSequential(new AutoMove(0.8, distance1, 0, kP_Straight));
	AddSequential(new Turn(turn1, kP_Turn)); //turn to 45 ////////////////// kP should NEVER below 1.0 it prevents overshooting
	AddSequential(new TimedShoot());

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
