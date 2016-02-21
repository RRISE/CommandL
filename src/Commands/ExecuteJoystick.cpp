#include "ExecuteJoystick.h"
#include "JoystickDrive.h"
#include "RetractSFM.h"
#include "ExtendSFM.h"
#include "Intake.h"
#include "ShootLowGoal.h"

ExecuteJoystick::ExecuteJoystick()
{
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.

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

	AddParallel(new JoystickDrive());

	joy_drive = CommandBase::pOI->GetDrive();
	joy_mech = CommandBase::pOI->GetDrive();

	if(joy_drive->GetTrigger(Joystick::kRightHand)){
		AddParallel(new RetractSFM());
	}else if(joy_drive->GetTrigger(Joystick::kLeftHand)){
		AddParallel(new ExtendSFM());
	}

	if(abs(joy_mech->GetPOV() - 180) < 10){ // D-pad: down
		AddParallel(new Intake());
	}else if(abs(joy_mech->GetPOV() - 0) < 10){ // D-pad: up
		AddParallel(new ShootLowGoal());
	}
}
