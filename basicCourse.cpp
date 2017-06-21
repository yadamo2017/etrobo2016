/*
スタートから走行ゴールまでの区間を走行するクラス
*/

#include "basicCourse.h"

#define RIGHT_EDGE  0
#define LEFT_EDGE   1

BasicCourse::BasicCourse(Mileage* mileage, Tracer* tracer, ChangeEdge* changeEdge){
	mMileage = mileage;
	mTracer = tracer;
	mChangeEdge = changeEdge;
	distance = 0;
	offset = 0;
	firstFlag = 0;
}

BasicCourse::~BasicCourse(){}

void BasicCourse::run(){
	if(firstFlag == 0){
		offset = (int)mMileage->getMileage();
		firstFlag = 1;
	} 

	char distance_chr[20] = {0};
	distance = (int)mMileage->getMileage() - offset;

	sprintf(distance_chr, "D=%3d",distance);
	ev3_lcd_draw_string(distance_chr, 0, 8*7+1);

	if(distance < 2000){
		mTracer->setEdge(RIGHT_EDGE);
		mTracer->setCommand(70, 0);
		mTracer->run();
	}else if(distance <2300){
		mTracer->setCommand(70, 0);
		mTracer->run();
	}else if(distance < 2800){
		mTracer->setCommand(50, 0);
		mTracer->run();
	}else if(distance <3300){
		mTracer->setCommand(50, 0);
		mTracer->run();
	}else if(distance < 4300){
		mTracer->setCommand(70, 0);
		mTracer -> run();
	}else if(distance < 4700){
		mTracer->setCommand(50, 0);
		mTracer->run();
	}else if(distance < 5400){
		mTracer->setCommand(50, 0);
		mTracer->run();
	}else if(distance < 5500){
		mTracer->setCommand(70, 0);
		mTracer->run();
	}else if(distance < 5550){
		mChangeEdge->edgeChange(RIGHT_EDGE, 70);
		mTracer->setEdge(LEFT_EDGE);
	}else if(distance < 8000){
		mTracer->setCommand(70, 0);
		mTracer->run();
	}/*else if(distance < 5800){
		mTracer->setCommand(70, 0);
		mTracer->run();
	}else if(distance < 6000)
		mTracer->setCommand(50, 0);
		mTracer->run();
	}else if(distance < 6500){
		mTracer->setCommand(50, -10);
		mTracer->run();
	}else if(distance < 7000){
		mTracer->setCommand(70, 0);
		mTracer->run();
	}
	*/
	else{
		mTracer->stop();
	}
}