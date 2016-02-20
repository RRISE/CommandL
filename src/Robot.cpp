#include "WPILib.h"
#include "Commands/Command.h"
#include "RobotMap.h"
#include "Commands/JoystickDrive.h"
#include "CommandBase.h"

class Robot: public IterativeRobot
{
private:
	Command* pAutonomousCommand;
	SendableChooser* pChooser;

	void RobotInit()
	{
		CommandBase::init();
		pChooser = new SendableChooser();
		// For testing purposes. Making sure to include
//		pChooser->AddDefault("Default Auto", new AutoShoot());
//		pChooser->AddObject("Drive Forward", new AutoDrive());
		Log();
		SmartDashboard::PutData("Auto Modes", pChooser);
	}
	
	void DisabledPeriodic()
	{
		Scheduler::GetInstance()->Run();
	}

	void AutonomousInit()
	{
		pAutonomousCommand = ((Command *)pChooser->GetSelected());
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
			SmartDashboard::PutNumber("Front Ultra", CommandBase::pDriveTrain->GetUltraAt(ULTRASONIC_LEFTFRONT_ANIPORT));
			SmartDashboard::PutNumber("Rear Ultra", CommandBase::pDriveTrain->GetUltraAt(ULTRASONIC_LEFTREAR_ANIPORT));
			SmartDashboard::PutNumber("Left Encoder Distance (inches)", CommandBase::pDriveTrain->GetLeftEncoderValue());
			SmartDashboard::PutNumber("Right Encoder Distance (inches)", CommandBase::pDriveTrain->GetRightEncoderValue());
	}
};

START_ROBOT_CLASS(Robot);

