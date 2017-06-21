/*
ET相撲を行うクラス
*/

#include "etzumo.h"

Etzumo::Etzumo(
	ColorMonitor* colorMonitor,
	LineMonitor* lineMonitor,
	Driver* driver,
	Mileage* mileage,
	Tracer* tracer
	){
		mColorMonitor = colorMonitor;
		mLineMonitor = lineMonitor;
		mDriver = driver;
		mMileage = mileage;
		mTracer = tracer;
		mClock = new ev3api::Clock();
		distance = 0;
		offset = 0;
		firstFlag = 0;
		time = 0;
}

Etzumo::~Etzumo(){}

void Etzumo::etzumoRun(int color){
	if(firstFlag == 0){
		offset = (int)mMileage->getMileage();
		firstFlag = 1;
	}

	distance = (int)mMileage->getMileage() - offset;

	if(distance < 100){
		mDriver->setCommand(30,0);
	}else{
		if(color == 0 || color == 1){
			if(catchBlack == 0){
				mTracer->setCommand(20, 0);
				mTracer->run();
				if(mLineMonitor->checkBrightness() < 10){
					catchBlack = 1;
					time = mClock->now();  
				} 
			}else{
				if(mClock->now() - time < 100){
					mDriver->setCommand(0,50);
					offset = mMileage->getMileage();
				}else{
					if(mMileage->getMileage() - offset < 100){
						mDriver->setCommand(20,0);
					}else{
						mDriver->setCommand(0,0);
					}
				}
			}
		}
	}
}

