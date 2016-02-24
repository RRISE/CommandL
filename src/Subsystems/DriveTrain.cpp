#include "DriveTrain.h"
#include "../RobotMap.h"
#include "Commands/ExecuteJoystick.h"

DriveTrain::DriveTrain() :
Subsystem("DriveTrain")
{
	pLeftFrontMotor = new CANTalon(TALON_LEFT_FRONT_DRIVE);
	pLeftRearMotor = new CANTalon(TALON_LEFT_REAR_DRIVE);
	pRightFrontMotor = new CANTalon(TALON_RIGHT_FRONT_DRIVE);
	pRightRearMotor = new CANTalon(TALON_RIGHT_REAR_DRIVE);

	pDipSwitchOne = new DigitalInput(0);
	pDipSwitchTwo = new DigitalInput(1);
	pDipSwitchThree = new DigitalInput(2);
	pDipSwitchFour = new DigitalInput(3);

	pLED1 = new DigitalOutput(14);

	// Assigns the Talons a device to receive feedback from
	pLeftFrontMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	pRightFrontMotor->SetFeedbackDevice(CANTalon::QuadEncoder);

	// Only front motor Talons have encoders


	// Encoder Pulses [SET PHYSICALLY USING DIP SWITCHES]
	pLeftFrontMotor->ConfigEncoderCodesPerRev(2048);
	pRightFrontMotor->ConfigEncoderCodesPerRev(2048);

	pGyro = new ADXRS450_Gyro();

	// Default sensitivity
	pGyro->Reset();

	pRobot = new RobotDrive(pLeftFrontMotor, pLeftRearMotor, pRightFrontMotor, pRightRearMotor);

	isReversed = true;
	pRobot->SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);
	pRobot->SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
	pRobot->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
	pRobot->SetInvertedMotor(RobotDrive::kRearRightMotor, true);

}

void DriveTrain::ReverseDrive(bool reverse){
	pRobot->SetInvertedMotor(RobotDrive::kFrontLeftMotor, reverse);
	pRobot->SetInvertedMotor(RobotDrive::kFrontRightMotor, reverse);
	pRobot->SetInvertedMotor(RobotDrive::kRearLeftMotor, reverse);
	pRobot->SetInvertedMotor(RobotDrive::kRearRightMotor, reverse);
	isReversed = reverse;
}

bool DriveTrain::IsReversed(){
	return isReversed;
}

void DriveTrain::InitDefaultCommand()
{
	SetDefaultCommand(new ExecuteJoystick()); //drive and tracks all triggers and D-Pad
}

void DriveTrain::Drive(Joystick* stick){
	double joyThreshold = 0.1;
	double reverseSign; // 1.0 for not reverse, -1.0 for reverse
	if(isReversed){
		reverseSign = 1.0;
	}else{
		reverseSign = -1.0; //for some reason, if you don't set motor inverse, joy X is reversed...
	}

	//copied from 2015 java project
	double stickX = stick->GetRawAxis(XBOX_L_XAXIS) * reverseSign;
	double stickY = stick->GetRawAxis(XBOX_L_YAXIS);
	SmartDashboard::PutNumber("Joy X", stickX);
	SmartDashboard::PutNumber("Joy Y", stickY);
	if(abs(stickX) > joyThreshold|| abs(stickY) > joyThreshold || true){ //debugging
		pRobot->ArcadeDrive(stickY, stickX, false);
	}else{
		pRobot->ArcadeDrive(0, 0, false);
	}

}




void DriveTrain::TankDrive(double leftAxis, double rightAxis)
{
	pRobot->TankDrive(leftAxis, rightAxis);
}

// Equations for encoders = encoder ticks * (2PIr)

int DriveTrain::GetLeftEncoderValue(){
	double data = pLeftFrontMotor->GetPosition();
	double equation = 2.0 * 3.141 * 3.0;

	return data * equation;
}

int DriveTrain::GetRightEncoderValue(){
	double data = pRightFrontMotor->GetPosition();
	double equation = 2.0 * 3.141 * 3.0;

	return data * equation;
}

void DriveTrain::LightLED() {
	pLED1->Set(1);
}


bool DriveTrain::GetSwitchPositionOne() {
	return pDipSwitchOne->Get();
}

bool DriveTrain::GetSwitchPositionTwo() {
	return pDipSwitchTwo->Get();
}

bool DriveTrain::GetSwitchPositionThree() {
	return pDipSwitchThree->Get();
}

bool DriveTrain::GetSwitchPositionFour() {
	return pDipSwitchFour->Get();
}

void DriveTrain::Turn(float speed, float direction)
{
	pRobot->Drive(speed, direction);
}

double DriveTrain::GetGyro(){
	return pGyro->GetAngle();
}

void DriveTrain::Calibrate(){
	pGyro->Calibrate();
}

void DriveTrain::ResetGyro(){
	pGyro->Reset();
}
