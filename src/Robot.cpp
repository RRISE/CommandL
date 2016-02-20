#include "WPILib.h"
#include "Commands/Command.h"
#include "RobotMap.h"
#include "Commands/JoystickDrive.h"
#include "Commands/AutoSequenceOne.h"
#include "Commands/AutoSequenceTwo.h"
#include "CommandBase.h"

class Robot: public IterativeRobot
{
private:
	Command* pAutonomousCommand;

	void RobotInit()
	{
		CommandBase::init();
		if(CommandBase::pDriveTrain->GetSwitchPositionOne() == true && CommandBase::pDriveTrain->GetSwitchPositionTwo() == false) {
			pAutonomousCommand = new AutoSequenceOne();
			CommandBase::pDriveTrain->LightLED();
		}

		if(CommandBase::pDriveTrain->GetSwitchPositionOne() == false && CommandBase::pDriveTrain->GetSwitchPositionTwo() == true) {
			pAutonomousCommand = new AutoSequenceTwo();
		}
		Log();
		//SmartDashboard::PutNumber("Auto Mode", pChooser);
	}
	
	void DisabledPeriodic()
	{
		Scheduler::GetInstance()->Run();
	}

	void AutonomousInit()
	{
		//CommandBase::pDriveTrain->ResetGyro();
		if (pAutonomousCommand != NULL)
			pAutonomousCommand->Start();
	}

	void AutonomousPeriodic()
	{
		Scheduler::GetInstance()->Run();
		Log();
	}

	void TeleopInit()
	{
		// This makes sure that the autonomous stops running when teleop starts running
		if (pAutonomousCommand != NULL)
			pAutonomousCommand->Cancel();
	}

	void TeleopPeriodic()
	{
		Scheduler::GetInstance()->Run();
		Log();
	}

	void TestPeriodic()
	{

	}

	void Log()
	{
			SmartDashboard::PutNumber("Gyro", CommandBase::pDriveTrain->GetGyro());
			SmartDashboard::PutBoolean("IsSwitchOne", CommandBase::pDriveTrain->GetSwitchPositionOne());
			SmartDashboard::PutBoolean("IsSwitchTwo", CommandBase::pDriveTrain->GetSwitchPositionTwo());
			SmartDashboard::PutBoolean("IsSwitchThree", CommandBase::pDriveTrain->GetSwitchPositionThree());
			SmartDashboard::PutBoolean("IsSwitchFour", CommandBase::pDriveTrain->GetSwitchPositionFour());
			SmartDashboard::PutNumber("Front Ultra", CommandBase::pBIOS->GetUltraAt(ULTRASONIC_FRONT_ANIPORT));
			SmartDashboard::PutNumber("Left Encoder Distance (inches)", CommandBase::pDriveTrain->GetLeftEncoderValue());
			SmartDashboard::PutNumber("Right Encoder Distance (inches)", CommandBase::pDriveTrain->GetRightEncoderValue());
	}
};

START_ROBOT_CLASS(Robot);

