#include "AutoMove.h"

AutoMove::AutoMove(double speed, double d_target, double a_target, double kP)
{
	Requires(CommandBase::pDriveTrain);
	this->d_target = d_target;
	this->a_target = a_target;
	this->speed = speed;
	this->kP = kP;
}

// Called just before this Command runs the first time
void AutoMove::Initialize()
{
	//CommandBase::pDriveTrain->pLeftFrontMotor -> SetPosition(0.0);
	//CommandBase::pDriveTrain->pRightFrontMotor -> SetPosition(0.0);

	this->d_target = CommandBase::pDriveTrain->GetRightEncoderValue() + d_target;

}

// Called repeatedly when this Command is scheduled to run
void AutoMove::Execute()
{
}

// Make this return true when this Command no longer needs to run execute()
bool AutoMove::IsFinished()
{
	bool isDone = CommandBase::pDriveTrain->GoForward(d_target, speed, a_target, kP);
	/*if(isDone){
		CommandBase::pDriveTrain->pLeftFrontMotor -> SetPosition(0.0);
		CommandBase::pDriveTrain->pRightFrontMotor -> SetPosition(0.0);
		return isDone;
	}else{
		return isDone; //return isDone anyways
	}*/
	return isDone;
}

// Called once after isFinished returns true
void AutoMove::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoMove::Interrupted()
{

}
