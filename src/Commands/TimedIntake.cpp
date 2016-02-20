#include "TimedIntake.h"

TimedIntake::TimedIntake()
{
	// Use Requires() here to declare subsystem dependencies
		Requires(CommandBase::pBIOS);
}

// Called just before this Command runs the first time
void TimedIntake::Initialize()
{
	CommandBase::pBIOS->StartTimer();
}

// Called repeatedly when this Command is scheduled to run
void TimedIntake::Execute()
{
	CommandBase::pBIOS->Intake(CommandBase::pBIOS->GetIntakeSpeed());
}

// Make this return true when this Command no longer needs to run execute()
bool TimedIntake::IsFinished()
{
	if(CommandBase::pBIOS->IsSwitchSet()){
		return false;
	}else{
		return true;
	}

}

// Called once after isFinished returns true
void TimedIntake::End()
{
	CommandBase::pBIOS->StopIntake();
	CommandBase::pBIOS->StopTimer();
	//CommandBase::pBIOS->InitializeCounter();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TimedIntake::Interrupted()
{

}
