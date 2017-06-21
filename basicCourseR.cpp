/*
スタートから走行ゴールまでの区間を走行するクラス
*/

#include "basicCourseR.h"

#define RIGHT_EDGE  0
#define LEFT_EDGE   1

BasicCourseR::BasicCourseR(Mileage* mileage, Tracer* tracer, ChangeEdge* changeEdge, StraightRunner* straightRunner, Logger* logger){
	mMileage = mileage;
	mTracer = tracer;
	mChangeEdge = changeEdge;
	mStraightRunner = straightRunner;
	mLogger = logger;
	distance = 0;
	offset = 0;
	firstFlag = 0;
	fase = 0;
}

BasicCourseR::~BasicCourseR(){}

bool BasicCourseR::run(){
	if(firstFlag == 0){
		offset = (int)mMileage->getMileage();
		mTracer->setMode(0);
		mTracer->setEdge(LEFT_EDGE);
		mTracer->changeGain(3);
		firstFlag = 11;
	}

	char distance_chr[20] = {0};
	distance = (int)mMileage->getMileage() - offset;

	sprintf(distance_chr, "D=%3d",distance);
	ev3_lcd_draw_string(distance_chr, 0, 8*7+1);

	switch(fase) {
	case 0:
		mTracer->setMode(0);
		mTracer->setEdge(LEFT_EDGE);
		fase = 1;
		break;
	case 1: //カーブ1
		mTracer->setCommand(20, 0);
		mTracer->run();
		if(distance >= 500) {
			fase = 2;
		}
		break;
	case 2: //直線1
		if(distance < 550) mTracer->setCommand(30, 0);
		else if(distance < 650) mTracer->setCommand(40, 0);
		else if(distance < 750) mTracer->setCommand(50, 0);
		else if(distance > 1500) mTracer->setCommand(50, 0);
		else if(distance > 1600) mTracer->setCommand(40, 0);
		else mTracer->setCommand(60, 0);
		mTracer->run();
		if(distance >= 1700) {
			mTracer->reset();
			mTracer->changeGain(2);
			fase = 3;
		}
		break;
	case 3: //カーブ2
		mTracer->setCommand(40, 9);
		mTracer->run();
		if(distance >= 2700) {
			mTracer->reset();
			mTracer->changeGain(2);
			fase = 4;
			//ev3_speaker_play_tone (NOTE_G4, 500);
		}
		break;
	case 4: //直線2
		if(distance < 2800) mTracer->setCommand(40, 0);
		else if(distance < 2900) mTracer->setCommand(50, 0);
		else if(distance < 3000) mTracer->setCommand(60, 0);
		else if(distance > 3650) mTracer->setCommand(60, 0);
		else if(distance > 3750) mTracer->setCommand(50, 0);
		else if(distance > 3850) mTracer->setCommand(40, 0);
		else if(distance > 3950) mTracer->setCommand(30, 0);
		//else mTracer->setCommand(70, 0);
		mTracer->run();
		if(distance >= 4050) {
			mTracer->reset();
			mTracer->changeGain(2);
			fase = 5;
		}
		break;
	case 5: //カーブ3
		mTracer->setCommand(20, -5);
		mTracer->run();
		if(distance >= 4300) {
			mTracer->reset();
			mTracer->changeGain(2);
			fase = 6;
		}
		break;
	case 6:
		mTracer->setCommand(30, 0);
		mTracer->run();
		if(distance >= 4600) {
			mTracer->reset();
			mTracer->changeGain(2);
			fase = 7;
		}
		break;
	case 7:
		mTracer->setCommand(20, -5);
		mTracer->run();
		if(distance >= 4850) {
			mTracer->reset();
			mTracer->changeGain(2);
			fase = 8;
		}
		break;
	case 8: //直線3
		if(distance < 4950) mTracer->setCommand(20, 0);
		else if(distance < 5050) mTracer->setCommand(30, 0);
		else if(distance < 5150) mTracer->setCommand(40, 0);
		else if(distance < 5250) mTracer->setCommand(50, 0);
		else if(distance < 5350) mTracer->setCommand(60, 0);
		else if(distance > 6600) mTracer->setCommand(60, 0);
		//else mTracer->setCommand(70, 0);
		mTracer->run();
		if(distance >= 6550) {
			mTracer->reset();
			mTracer->changeGain(2);
			fase = 9;
		}
		break;
	case 9: //カーブ4
		mTracer->setCommand(40, -5);
		mTracer->run();
		if(distance >= 7050) {
			mTracer->reset();
			mTracer->changeGain(2);
			fase = 10;
		}
		break;
	case 10: //直線4
		if(distance < 7450) mTracer->setCommand(50, 0);
		else if(distance < 7700) mTracer->setCommand(60, 0);
		//else if(distance < 7500) mTracer->setCommand(70, 0);
		// else if(distance < 7800) mTracer->setCommand(80, 0);
		// else if(distance < 8400) mTracer->setCommand(90, 0);
		//else mTracer->setCommand(70, 0);
		mTracer->run();
		if(distance >= 7700) {
			//mTracer->stop();
			mTracer->reset();
			mTracer->changeGain(3);
			fase = 11;
			//ev3_speaker_play_tone (NOTE_G4, 500);
		}
		break;
	case 11:
		//mStraightRunner->setForward(70);
		//mStraightRunner->straightRun();
		mTracer->setCommand(70,0);
		mTracer->run();

		if(distance >= 10000) {
			fase = 20;
		}
		break;
	default:
		mTracer->stop();
		return false;
		break;
	}

	return true;
}