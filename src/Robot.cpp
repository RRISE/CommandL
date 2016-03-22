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
	SendableChooser autoChooser;

	void RobotInit()
	{
		CommandBase::init();

		// instantiate the command used for the autonomous period
		autoChooser.AddDefault("Spy Bot Position", new AutoSequenceOne());
		autoChooser.AddObject("Low Bar Position", new AutoSequenceTwo());
		SmartDashboard::PutData("Auto Mode", &autoChooser);


		if(CommandBase::pDriveTrain->GetSwitchPositionOne() == true && CommandBase::pDriveTrain->GetSwitchPositionTwo() == false) {
			pAutonomousCommand = new AutoSequenceOne();
			CommandBase::pDriveTrain->LightLED();
		}

		if(CommandBase::pDriveTrain->GetSwitchPositionOne() == false && CommandBase::pDriveTrain->GetSwitchPositionTwo() == true) {
			pAutonomousCommand = new AutoSequenceTwo();
		}
		Log();
	}

	void DisabledPeriodic()
	{
		Scheduler::GetInstance()->Run();
	}

	void AutonomousInit()
	{

		pAutonomousCommand = (Command *)autoChooser.GetSelected();
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
		SmartDashboard::PutNumber("Front Ultra", CommandBase::pBIOS->GetUltraAt(ULTRASONIC_FRONT_ANIPORT));
		SmartDashboard::PutNumber("Encoder Distance", CommandBase::pDriveTrain->GetRightEncoderValue());
		CameraServer::GetInstance()->SetQuality(50);
		CameraServer::GetInstance()->StartAutomaticCapture("cam0");

	}
};

START_ROBOT_CLASS(Robot);

