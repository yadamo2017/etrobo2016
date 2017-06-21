/*
走行距離を管理するクラス
*/

#include "mileage.h"
#include <math.h>

//#define abs(a) ((a) < 0 ? -(a) : (a))
#define TYRE    82
#define ENC90	206

Mileage::Mileage(ev3api::Motor* leftMotor, ev3api::Motor* rightMotor)
	:
mLeftMotor(leftMotor),
	mRightMotor(rightMotor)
{

	distanceT = 0; // 走行体の走った距離
	distanceR = 0; // 右タイヤの走った距離
	distanceL = 0; // 左タイヤの走った距離

}

Mileage::~Mileage()
{}




double Mileage::getMileage(){

	distanceT = (mileageL() + mileageR()) / 2; //走行体の走行距離の計算

	return distanceT;


}

double Mileage::mileageL(){

	motor_ang_l = mLeftMotor->getCount();

	motorcountL = motor_ang_l;

	// 各タイヤの走行距離計算[mm]
	distanceL = TYRE * M_PI * motorcountL / 360;

	return distanceL;
}

double Mileage::mileageR(){

	motor_ang_r = mRightMotor->getCount();

	motorcountR = motor_ang_r;

	// 各タイヤの走行距離計算[mm]
	distanceR = TYRE * M_PI * motorcountR / 360;

	return distanceR;
}

void Mileage::init(){
	distanceL = 0;
	distanceR = 0;
	distanceT = 0;
	mRightMotor->reset();
	mLeftMotor->reset();
}

int Mileage::orientation(){
	motorcountL = this->mileageL();
	motorcountR = this->mileageR();

	if(motorcountL-motorcountR >= 0){
		return (int)(((motorcountL-motorcountR)%(ENC90*4))/(ENC90/3));
	}else{
		return 12+(int)(((motorcountL-motorcountR)%(ENC90*4))/(ENC90/3));
	}
}