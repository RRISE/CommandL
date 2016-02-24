#ifndef ExecuteJoystick_H
#define ExecuteJoystick_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include "RobotMap.h"


class ExecuteJoystick: public CommandGroup
{
public:
	ExecuteJoystick();
	Joystick* joy_drive;
	Joystick* joy_mech;
};

#endif
