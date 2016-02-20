#include "SFM.h"
#include "Commands/Subsystem.h"
#include "../RobotMap.h"

#include "Commands/ExtendSFM.h"

SFM::SFM() :
		Subsystem("SFM")
{
	//solenoid forcing module
	compressor = new Compressor(0);
	sfm = new DoubleSolenoid(0, 1);


	compressor->Start();

	sfm->Set(DoubleSolenoid::kOff);

}

void SFM::InitDefaultCommand()
{
	SetDefaultCommand(new ExtendSFM());
}


void SFM::SetForward()
{
	sfm->Set(DoubleSolenoid::kForward);
}

void SFM::SetReverse()
{
	sfm->Set(DoubleSolenoid::kReverse);
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
