/*
走行前のキャリブレーションを行うクラス
*/

#include "calibration.h"

#define CALIB_FONT_WIDTH (6/*TODO: magic number*/)
#define CALIB_FONT_HEIGHT (8/*TODO: magic number*/)

Calibration::Calibration(
	ev3api::TouchSensor* touchSensor,
	LineMonitor* lineMonitor,
	ColorMonitor* colorMonitor
	):
mTouchSensor(touchSensor)
{
	mLineMonitor = lineMonitor;
	mColorMonitor = colorMonitor;
	clock = new ev3api::Clock();
}

Calibration::~Calibration(){}

/*
キャリブレーションを行う
app.cppのmain_taskで呼び出され、引数にカラーセンサーから取得した値を代入する
*/

void Calibration::calibrate(rgb_raw_t* rgb, int8_t& black, int8_t& white){
	char red[20] = {0};
	char blue[20] = {0};
	char green[20] = {0};
	char black_chr[20] ={0};
	char white_chr[20] ={0};
	int push_count = 0;

	while(1){

		if (mTouchSensor->isPressed()){
			switch(push_count){
			case 0:
				mColorMonitor->checkColor(rgb[push_count]);
				sprintf(red, "R=%3d", (int)rgb[push_count].r);
				sprintf(green, "G=%3d", (int)rgb[push_count].g);
				sprintf(blue, "B=%3d", (int)rgb[push_count].b);           

				ev3_lcd_draw_string("Red area", 0, CALIB_FONT_HEIGHT*2+1);
				ev3_lcd_draw_string(red, 0, CALIB_FONT_HEIGHT*3+1);
				ev3_lcd_draw_string(green, CALIB_FONT_WIDTH*6, CALIB_FONT_HEIGHT*3+1);
				ev3_lcd_draw_string(blue, CALIB_FONT_WIDTH*12, CALIB_FONT_HEIGHT*3+1);

				push_count = 1;    
				break;
			case 1:
				mColorMonitor->checkColor(rgb[push_count]);
				sprintf(red, "R=%3d", (int)rgb[push_count].r);
				sprintf(green, "G=%3d", (int)rgb[push_count].g);
				sprintf(blue, "B=%3d", (int)rgb[push_count].b);           

				ev3_lcd_draw_string("Blue area", 0, CALIB_FONT_HEIGHT*5+1);
				ev3_lcd_draw_string(red, 0, CALIB_FONT_HEIGHT*6+1);
				ev3_lcd_draw_string(green, CALIB_FONT_WIDTH*6, CALIB_FONT_HEIGHT*6+1);
				ev3_lcd_draw_string(blue, CALIB_FONT_WIDTH*12, CALIB_FONT_HEIGHT*6+1);

				push_count= 3;    
				break;
			case 2:
				mColorMonitor->checkColor(rgb[push_count]);
				sprintf(red, "R=%3d", (int)rgb[push_count].r);
				sprintf(green, "G=%3d", (int)rgb[push_count].g);
				sprintf(blue, "B=%3d", (int)rgb[push_count].b);           

				ev3_lcd_draw_string("Green area", 0, CALIB_FONT_HEIGHT*8+1);
				ev3_lcd_draw_string(red, 0, CALIB_FONT_HEIGHT*9+1);
				ev3_lcd_draw_string(green, CALIB_FONT_WIDTH*6, CALIB_FONT_HEIGHT*9+1);
				ev3_lcd_draw_string(blue, CALIB_FONT_WIDTH*12, CALIB_FONT_HEIGHT*9+1);

				push_count++;    
				break;
			case 3:
				black = mLineMonitor->checkBrightness();
				sprintf(black_chr, "black = %3d", (int)black);
				ev3_lcd_draw_string(black_chr, 0, CALIB_FONT_HEIGHT*11+1);
				push_count++;
				break;
			case 4:
				white = mLineMonitor->checkBrightness();
				sprintf(white_chr, "white = %3d", (int)white);
				ev3_lcd_draw_string(white_chr, 0, CALIB_FONT_HEIGHT*12+1);
				push_count=10;
				break;
			case 10:
				goto endloop;
				break;
			}
			clock->wait(1000);
		}

	}   
endloop: ;
}

