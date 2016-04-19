#include "WPILib.h"
#include "Commands/Command.h"
#include "RobotMap.h"
#include "Commands/JoystickDrive.h"
#include "Commands/AutoSequenceOne.h"
#include "Commands/AutoSequenceTwo.h"
#include "Commands/AutoSequenceThree.h"
#include "Commands/AutoSequenceFour.h"
#include "Commands/AutoSequenceFive.h"
#include "Commands/AutoSequenceSix.h"
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


		autoChooser.AddDefault("Just charge", new AutoSequenceFive());
		autoChooser.AddObject("Low Bar, no shoot", new AutoSequenceSix());
		autoChooser.AddObject("Spy Bot Position", new AutoSequenceOne());
		autoChooser.AddObject("Low Bar Position", new AutoSequenceTwo());
		autoChooser.AddObject("Shoot Only", new AutoSequenceFour());
		autoChooser.AddObject("Just Chill", new AutoSequenceThree());
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


		SmartDashboard::PutString("Just Chill", "Auto_3");
		SmartDashboard::PutString("Just Charge", "Auto_5");
		SmartDashboard::PutString("Low Bar Position", "Auto_2");
		SmartDashboard::PutString("Low Bar, no shoot", "Auto_2");
		SmartDashboard::PutString("Spy Bot Position", "Auto_1");
		SmartDashboard::PutString("Just Shoot", "Auto_4");

		//CameraServer::GetInstance()->SetQuality(50);
		//CameraServer::GetInstance()->StartAutomaticCapture("cam0");

	}
};

START_ROBOT_CLASS(Robot);

