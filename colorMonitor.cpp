/*
色情報を調べるクラス
*/

#include "ColorMonitor.h"

#define RED		0
#define GREEN	1
#define BLUE	2
#define YELLOW	3
#define BLACK	4

#define JUDGE_LINE	20

#define abs(a) ((a) < 0 ? -(a) : (a))

rgb_raw_t setColor(uint16_t r, uint16_t g, uint16_t b);

ColorMonitor::ColorMonitor(
	ev3api::ColorSensor* colorSensor,
	Logger* logger
	):mColorSensor(colorSensor){
		mLogger=logger;

		/*
		color[RED] = setColor(158,19,12);
		color[GREEN] = setColor(24,105,21);
		color[BLUE] = setColor(16,55,92);
		color[YELLOW] = setColor(110,180,26);
		*/

		color[RED] = setColor(148,28,22);
		color[GREEN] = setColor(20,87,20);
		color[BLUE] = setColor(15,90,144);
		color[YELLOW] = setColor(155,185,23);

		blockColor[RED] = setColor(97, 18, 8);
		blockColor[GREEN] = setColor(11, 61, 16);
		blockColor[BLUE] = setColor(9, 68, 115);
		blockColor[YELLOW] = setColor(136, 142, 10);
		blockColor[BLACK] = setColor(0, 1, 1);

}

ColorMonitor::~ColorMonitor(){}

/*色のrgbを調べる*/
void ColorMonitor::checkColor(rgb_raw_t& rgb){
	mColorSensor->getRawColor(rgb);
	//mLogger->addData(rgb.r);
	//mLogger->addData(rgb.g);
	//mLogger->addData(rgb.b);
}

int ColorMonitor::colorJudge(rgb_raw_t& rgb, char arm){
	if(arm == 0){
		for(int i=0; i<4; i++){
			if(abs(rgb.r - color[i].r) < JUDGE_LINE && abs(rgb.g - color[i].g) < JUDGE_LINE && abs(rgb.b - color[i].b) < JUDGE_LINE){
				return i;
			}
		}
	}else{

		for(int i=0; i<5; i++){
			if(abs(rgb.r - blockColor[i].r) < JUDGE_LINE && abs(rgb.g - blockColor[i].g) < JUDGE_LINE && abs(rgb.b - blockColor[i].b) < JUDGE_LINE){
				return i;
			}
		}
	}
	return 10;
}

int ColorMonitor::colorJudge2(rgb_raw_t& rgb, char arm){

	//if(rgb.b > rgb.g+10 && rgb.g > rgb.r+10 && rgb.b > rgb.r && rgb.b > 50 && rgb.r < 50) return 2;
	if(rgb.b > 50 && rgb.r < 30 && rgb.b > rgb.g) return 2;
	else if(rgb.r > 100 && rgb.g > 100 && rgb.b < 50 && rgb.g > rgb.r) return 3;
	else if(rgb.r > 50 && rgb.g < 50 && rgb.b < 50) return 0;
	else if(rgb.g > rgb.r+rgb.b+20 && rgb.r < 50 && rgb.b < 50) return 1;
	else if(rgb.r < 10 && rgb.g < 10 && rgb.b < 10 && arm==1) return 4;
	else return 10;	

}

rgb_raw_t setColor(uint16_t r, uint16_t g, uint16_t b){
	rgb_raw_t color = {r, g, b};
	return color;
}