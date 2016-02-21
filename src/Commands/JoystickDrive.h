#ifndef JoystickDrive_H
#define JoystickDrive_H

#include "../CommandBase.h"
#include "WPILib.h"

class JoystickDrive: public CommandGroup
{
public:
	JoystickDrive();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
