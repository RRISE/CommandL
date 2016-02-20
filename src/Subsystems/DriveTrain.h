#ifndef DriveTrain_H
#define DriveTrain_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class DriveTrain: public Subsystem
{
private:
	RobotDrive* pRobot;
	AnalogInput* pLeftFrontUltra;
	AnalogGyro* pGyro;
	CANTalon* pLeftFrontMotor;
	CANTalon* pLeftRearMotor;
	CANTalon* pRightFrontMotor;
	CANTalon* pRightRearMotor;
public:
	DriveTrain();
	void InitDefaultCommand();
	void Drive(Joystick* stick);
	void TankDrive(double leftAxis, double rightAxis);
	int GetLeftEncoderValue();
	int GetRightEncoderValue();
	double GetUltraAt(int presetPort);
	double GetGyro();
	void ResetGyro();
};

#endif
