#include "RotateWithGyro.h"

RotateWithGyro::RotateWithGyro(double degrees)
{
	Requires(CommandBase::pDriveTrain);
	this->degrees = degrees;
	refPoint = 0.0;

}

// Called just before this Command runs the first time
void RotateWithGyro::Initialize()
{
	refPoint = CommandBase::pDriveTrain->GetGyro();
	SetTimeout(5);
}

// Called repeatedly when this Command is scheduled to run
void RotateWithGyro::Execute()
{
	if(degrees > 0) {
		CommandBase::pDriveTrain->Turn(1.0f, -1.0f); // Adjust
	} else {
		CommandBase::pDriveTrain->Turn(1.0f, 1.0f); // Needs adjusting badly
	}
}

// Make this return true when this Command no longer needs to run execute()
bool RotateWithGyro::IsFinished()
{
	if(IsTimedOut()){ //time out
		return true;
	}

	if (degrees > 0) {
		if (CommandBase::pDriveTrain->GetGyro() - refPoint < degrees) {
			return false;
		}
		return true;
	} else {
		if(refPoint - CommandBase::pDriveTrain->GetGyro() < abs(degrees)) {
			return false;
		}
		return true;
	}
}

// Called once after isFinished returns true
void RotateWithGyro::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RotateWithGyro::Interrupted()
{
	End();
}
