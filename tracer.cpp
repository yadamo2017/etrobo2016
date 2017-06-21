/*
ライントレースを行うクラス
*/

#include "tracer.h"

#define LIGHT_WHITE     40
#define LIGHT_BLACK     0

#define TARGET		100

#define RIGHT_EDGE  0
#define LEFT_EDGE   1

#define ALPHA	0.9

Tracer::Tracer(
	Driver* driver,
	LineMonitor* lineMonitor,
	Logger* logger,
	ColorMonitor* colorMonitor
	){
		mDriver = driver;
		mLineMonitor = lineMonitor;
		mLogger = logger;
		mColorMonitor = colorMonitor;
		pid = new Pid();
		forward = 0;
		turn = 0;
		bright = 0;
		curvature = 0;
		black = LIGHT_BLACK;
		white = LIGHT_WHITE;
		edge = 0;
		buff[0] = 0;
		buff[1] = 0;
		firstFlag = false;
		
		color = colorInit(0, 0, 0);
		mode=0;
		colorAverage = 0;

		blackAverage = 0;
		whiteAverage = 0;

		kp = 0.1;
		ki = 0.000001;
		kd = 0.005;
}

Tracer::~Tracer(){}

void Tracer::run(){


	/*
	if (mLineMonitor->checkBrightness() >= (LIGHT_WHITE + LIGHT_BLACK)/2)
	{
	turn =  20; 
	}
	else
	{
	turn = -20; 
	} 
	*/
	if(mode == 0){
		buff[0] = (((float)mLineMonitor->checkBrightness() - (float)black)/((float)white - (float)black))*200.0;
	}else if(mode == 1){
		mColorMonitor->checkColor(color);
		colorAverage = (color.r+color.g+color.b)/3;

		buff[0] = (((float)colorAverage - (float)blackAverage)/((float)whiteAverage - (float)blackAverage))*200.0;
	}



	//mLogger->addData(buff[0]);
	
	if(buff[0]<0) buff[0] = 0;
	else if(buff[1]>200) buff[1] = 200;
	
	if(firstFlag == false){
		bright = buff[0];
		firstFlag = true;
	}else{
		bright = buff[0]*(1-ALPHA)+buff[1]*ALPHA;    
	}
	
	//bright = buff[0];
	//mLogger->addData(buff[0]);
	//mLogger->addData(bright);
	
	//pid->setGain(0.28, 0.00001, 0.01);
	//pid->setGain(0.28, 0.00001, 0.005);
	//pid->setGain(0.12, 0.000001, 0.008);
	pid->setGain(kp, ki, kd);

	if(edge == RIGHT_EDGE) turn = (int)pid->pidControl(bright, 80);
	else turn = -(int)pid->pidControl(bright, 80);

	if(turn > 100) turn = 100;
	else if(turn < -100) turn = -100;

	char chr[10] = {0};
	sprintf(chr, "PID=%.4d", turn);
	ev3_lcd_draw_string(chr, 0, 8*5+1);

	mDriver->setCommand(forward,turn + curvature);

	buff[1] = bright;
}

void Tracer::stop(){
	if(forward > 0) forward -= 0.5;
	else if(forward < 0) forward+=0.5;
	else forward = 0;
	mDriver->setCommand(forward, 0);
	pid->reset();
}

void Tracer::setTargetBrightness(int8_t _black, int8_t _white){
	black = _black;
	white = _white;
}

void Tracer::setTargetColor(rgb_raw_t _blackColor, rgb_raw_t _whiteColor){
	blackColor = _blackColor;
	whiteColor = _whiteColor;

	blackAverage = (blackColor.r+blackColor.g+blackColor.b)/3;
	whiteAverage = (whiteColor.r+whiteColor.g+whiteColor.b)/3;
}

void Tracer::setCommand(int8_t _forward, int _curvature){
	forward = _forward;
	curvature = _curvature;
}

void Tracer::setEdge(char _edge){
	edge = _edge;
}

void Tracer::reset(){
	firstFlag = false;
	pid->reset();
}

void Tracer::setMode(int _mode){
	mode = _mode;
}

void Tracer::changeGain(int course) {
	if(course == 0) {
		kp = 0.1;
		ki = 0.000001;
		kd = 0.005;
	} else if(course == 1) {
		kp = 0.15;
		ki = 0.000001;
		kd = 0.005;
	}
	else if(course == 2) {
		kp = 0.12;
		ki = 0.000001;
		kd = 0.008;
	}
	 else if(course == 3) {
		kp = 0.15;
		ki = 0.000001;
		kd = 0.01;
	}
}


rgb_raw_t Tracer::colorInit(uint16_t r, uint16_t g, uint16_t b){
	rgb_raw_t i = {r, g, b};
	return i;
}