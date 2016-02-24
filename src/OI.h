#ifndef OI_H
#define OI_H

#include "WPILib.h"


class OI
{
private:

public:
	OI();
	Joystick* GetDrive();
	Joystick* GetMech();

	Joystick* xbox_drive; //drive xbox
	Joystick* xbox_mech; //mech xbox

	//NOTE: all triggers are handled in ExecuteJoystick command
	//JoystickButton* xbox_drive_right_trigger;
	//JoystickButton* xbox_drive_left_trigger;
	JoystickButton* xbox_drive_button_A;

	JoystickButton* xbox_mech_button_A;
	JoystickButton* xbox_mech_button_B;
	JoystickButton* xbox_mech_button_X;
	JoystickButton* xbox_mech_button_Y;

	JoystickButton* xbox_mech_button_start;
	JoystickButton* xbox_mech_button_back;
	JoystickButton* xbox_drive_button_start;
	JoystickButton* xbox_drive_button_back;


};

#endif
