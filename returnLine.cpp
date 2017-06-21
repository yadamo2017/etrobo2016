/*
ライン復帰するクラス
*/

#include "returnLine.h"

ReturnLine::ReturnLine(StraightRunner* straightRunner, Revolver* revolver, LineMonitor* lineMonitor, Mileage* mileage){
	mStraightRunner = straightRunner;
	mRevolver = revolver;
	mLineMonitor = lineMonitor;
	mMileage = mileage;

	fase = 0;

	firstFlag = false;
	mile = 0;
	bright = 0;

	timeCount = 0;

}

ReturnLine::~ReturnLine(){}

bool ReturnLine::lineReturn(int direction){
	if(!firstFlag){
		buff = mMileage->getMileage();
		mStraightRunner->reset();
		mRevolver->reset();
		timeCount = 0;
		fase = 1;
		firstFlag = true;
	}

	mile = mMileage->getMileage() - buff;

	switch(fase){
	case 0:
		if(timeCount++ < 200){
			mStraightRunner->stop();
		}else{
			mStraightRunner->setForward(20);
			mStraightRunner->straightRun();
			if(mile > 20){
				buff = mMileage->getMileage();
				mStraightRunner->reset();
				mRevolver->reset();
				timeCount = 0;
				fase = 1;
			}
		}
		break;

	case 1:
		if(timeCount<200){
			timeCount++;
			mStraightRunner->stop();
		}else{
			mStraightRunner->setForward(-10);
			mStraightRunner->straightRun();
			bright = mLineMonitor->checkBrightness();
			if(bright < 10){
				buff = mMileage->getMileage();
				mRevolver->reset();
				mStraightRunner->reset();
				timeCount = 0;
				fase = 3;
			}
		}
		break;

	case 3:
		if(timeCount++ < 200){
			mStraightRunner->stop();
		}else{
			mStraightRunner->setForward(20);
			mStraightRunner->straightRun();
			if(mile > 35){
				buff = mMileage->getMileage();
				mStraightRunner->reset();
				mRevolver->reset();
				timeCount = 0;
				fase = 4;
			}
		}
		break;

	case 4:

		mRevolver->setForward(0);
		bright = mLineMonitor->checkBrightness();
		if(mRevolver->revolve(110*direction)||bright<10){
			buff = mMileage->getMileage();
			mRevolver->reset();
			mStraightRunner->reset();
			timeCount = 0;
			fase = 5;
		}


		break;

	case 5:
		if(timeCount++<200){
			mStraightRunner->stop();
		}else{
			mRevolver->setForward(0);
			firstFlag = false;
			return true;
		}
		break;
	}

	return false;
}