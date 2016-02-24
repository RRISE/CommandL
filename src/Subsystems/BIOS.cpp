#include "BIOS.h"
#include "Commands/RumbleInRange.h"
#include "../RobotMap.h"

BIOS::BIOS() :
Subsystem("BIOS")
{
	pCollectorMotor = new CANTalon(TALON_COLLECTOR);
	pShooterMotorRight = new CANTalon(TALON_RIGHT_SHOOTER);
	pShooterMotorLeft = new CANTalon(TALON_LEFT_SHOOTER);

	pShooterMotorLeft->SetInverted(true);

	prefs = Preferences::GetInstance();
	fShootSpeed = prefs->GetFloat("ShootSpeed", 0.0f);
	fIntakeSpeed = prefs->GetFloat("IntakeSpeed", 0.0f);
	fKickerSpeed = prefs->GetFloat("KickerSpeed", 0.0f);
	//fRegressionSpeed = 0.0;

	limitSwitch = new DigitalInput(LIMIT_SWITCH_1);
	counter = new Counter(limitSwitch);
	frontUltra = new AnalogInput(ULTRASONIC_FRONT_ANIPORT);

	pTimer = new Timer;
}


void BIOS::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new RumbleInRange());
}

void BIOS::Intake(float speed)
{
	pCollectorMotor->Set(-speed);
}

void BIOS::Shoot(float speed)
{
	pShooterMotorRight->Set(speed);
	pShooterMotorLeft->Set(speed);
}

void BIOS::RumbleWhenRange(double target, double variance){
	if(abs(GetUltraAt(ULTRASONIC_FRONT_ANIPORT) - target) <= variance){
		CommandBase::pOI->GetDrive()->SetRumble(Joystick::RumbleType::kLeftRumble, 1.0f);
		CommandBase::pOI->GetMech()->SetRumble(Joystick::RumbleType::kLeftRumble, 1.0f);
	}else{
		CommandBase::pOI->GetDrive()->SetRumble(Joystick::RumbleType::kLeftRumble, 0.0f);
		CommandBase::pOI->GetMech()->SetRumble(Joystick::RumbleType::kLeftRumble, 0.0f);
	}
}

void BIOS::StopIntake()
{
	pCollectorMotor->Set(0);
}

void BIOS::StopShoot()
{
	pShooterMotorRight->Set(0);
	pShooterMotorLeft->Set(0);
}

void BIOS::LowGoal()
{
	pCollectorMotor->Set(prefs->GetFloat("LowGoalSpeed", 0.75f));
}

void BIOS::StartTimer()
{
	pTimer->Start();
}

double BIOS::GetCurrentTime()
{
	return pTimer->Get();
}

void BIOS::StopTimer()
{
	pTimer->Stop();
	pTimer->Reset();
}


float BIOS::GetShootSpeed()
{
	fShootSpeed = prefs->GetFloat("ShootSpeed", 0.6f);
	return fShootSpeed;
}

float BIOS::GetShootSpeed(double displacement)
{
	fShootSpeed = speedMap[displacement];
	return fShootSpeed;
}

float BIOS::GetIntakeSpeed()
{
	fIntakeSpeed = prefs->GetFloat("IntakeSpeed", 0.5f);
	return fIntakeSpeed;
}

float BIOS::GetKickerSpeed(){
	fKickerSpeed = prefs->GetFloat("KickerSpeed", 1.0f);
	return fKickerSpeed;
}

bool BIOS::IsSwitchSet() {
	return limitSwitch->Get();
	//return counter->Get() > 0;
}

void BIOS::InitializeCounter() {
	counter->Reset();
}

double BIOS::GetTempFromPref(){
	return prefs->GetFloat("Temperature", 25.0f); //assume 25 degrees
}

double BIOS::GetUltraAt(int port){
	double Vm = 0; //analog voltage from sensor
	double Tc = GetTempFromPref(); //temperature, human input
	double Vcc = VCC; //5V supply

	switch(port){
	case ULTRASONIC_FRONT_ANIPORT:
		Vm = frontUltra->GetAverageVoltage();
		break;
	default:
		Vm = 9999.9; //impossible value
		break;
	}
	//return rawReading * ULTRASONIC_READING_TO_INCH / ULTRASONIC_SCALEFACTOR; //empirical
	return (Vm/(Vcc/1024) * (58 * pow(10,-6)) * (20.05 * pow((Tc + 273.15), 0.5)/2)); //return value in meteres with temp compensation
}


// Put methods for controlling this subsystem
// here. Call these from Commands.
