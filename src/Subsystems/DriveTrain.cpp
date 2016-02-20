#include "DriveTrain.h"
#include "../RobotMap.h"
#include "Commands/JoystickDrive.h"

DriveTrain::DriveTrain() :
		Subsystem("DriveTrain")
{
	pLeftFrontMotor = new CANTalon(TALON_LEFT_FRONT_DRIVE);
	pLeftRearMotor = new CANTalon(TALON_LEFT_REAR_DRIVE);
	pRightFrontMotor = new CANTalon(TALON_RIGHT_FRONT_DRIVE);
	pRightRearMotor = new CANTalon(TALON_RIGHT_REAR_DRIVE);


	// Assigns the Talons a device to receive feedback from
	pLeftFrontMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	pRightFrontMotor->SetFeedbackDevice(CANTalon::QuadEncoder);

	// Only front motor Talons have encoders


	// Encoder Pulses [SET PHYSICALLY USING DIP SWITCHES]
	pLeftFrontMotor->ConfigEncoderCodesPerRev(2048);
	pRightFrontMotor->ConfigEncoderCodesPerRev(2048);

	pLeftFrontUltra = new AnalogInput(ULTRASONIC_LEFTFRONT_ANIPORT);

	pGyro = new AnalogGyro(0);

	// Default sensitivity
	pGyro->SetSensitivity(0.007);
	pGyro->Reset();

	pRobot = new RobotDrive(pLeftFrontMotor, pLeftRearMotor, pRightFrontMotor, pRightRearMotor);
}

void DriveTrain::InitDefaultCommand()
{
	SetDefaultCommand(new JoystickDrive());
}

void DriveTrain::Drive(Joystick* stick){
	pRobot->ArcadeDrive(stick);
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

double DriveTrain::GetUltraAt(int presetPort){
	switch(presetPort){
		case 5:
			return pLeftFrontUltra->GetAverageVoltage() * ULTRASONIC_READING_TO_INCH / ULTRASONIC_SCALEFACTOR;
			break;
		case 3:
			//return leftRearUltra->GetAverageVoltage() * ULTRASONIC_READING_TO_INCH / ULTRASONIC_SCALEFACTOR;
			return 9999.9;
			break;
		default:
			return 9999.9; //impossible value
	}
}

double DriveTrain::GetGyro(){
	return pGyro->GetAngle();
}

void DriveTrain::ResetGyro(){
	pGyro->Reset();
}
