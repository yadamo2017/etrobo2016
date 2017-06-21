#ifndef EV3_UNIT_RETURNLINE_H_
#define EV3_UNIT_RETURNLINE_H_

#include "ev3api.h"
#include "StraightRunner.h"
#include "revolver.h"
#include "lineMonitor.h"

class ReturnLine{
public:
	ReturnLine(StraightRunner* straightRunner, Revolver* revolver, LineMonitor* lineMonitor, Mileage* mileage);
	~ReturnLine();

	bool lineReturn(int direction);

private:
	StraightRunner* mStraightRunner;
	Revolver* mRevolver;
	LineMonitor* mLineMonitor;
	Mileage* mMileage;

	int fase;
	bool firstFlag;

	double mile;
	double buff;
	int bright;
	int timeCount;
};

#endif