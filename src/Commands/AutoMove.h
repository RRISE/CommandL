#ifndef AutoMove_H
#define AutoMove_H

#include "../CommandBase.h"
#include "WPILib.h"

class AutoMove: public CommandBase
{
public:
	AutoMove(double speed, double d_target, double a_target, double kP);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	double speed;
	double kP;
	double d_target;
	double a_target;
};

#endif
