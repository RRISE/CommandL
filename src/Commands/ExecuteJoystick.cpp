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

	//bad attempt
	/*
	joy_drive = CommandBase::pOI->GetDrive();
	joy_mech = CommandBase::pOI->GetMech();

	if(joy_drive->GetRawAxis(XBOX_R_TRIGGER)){
		AddParallel(new RetractSFM());
	}else if(joy_drive->GetRawAxis(XBOX_L_TRIGGER)){
		AddParallel(new ExtendSFM());
	}


	SmartDashboard::PutNumber("Drive Right Trigger",joy_drive->GetRawAxis(XBOX_R_TRIGGER));
	SmartDashboard::PutNumber("Drive Left Trigger",joy_drive->GetRawAxis(XBOX_L_TRIGGER));
	SmartDashboard::PutNumber("Mech POV", joy_mech->GetRawAxis(6));


	if(abs(joy_mech->GetPOV() - 180) < 10){ // D-pad: down
		AddParallel(new Intake());
	}else if(abs(joy_mech->GetPOV() - 0) < 10 && joy_mech->GetPOV() != -1){ // D-pad: up
		AddParallel(new ShootLowGoal());
	}*/
}
