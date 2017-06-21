/*
ラインの輝度をチェックするクラス
*/

#include "lineMonitor.h"

LineMonitor::LineMonitor(
	ev3api::ColorSensor* colorSensor,
	Logger* logger
	):
mColorSensor(colorSensor){
	mLogger = logger;	
}

LineMonitor::~LineMonitor(){}


/*輝度を調べる*/
int8_t LineMonitor::checkBrightness(){
	brightness = mColorSensor->getBrightness();
	//mLogger->addData(brightness);
	return brightness;
}
