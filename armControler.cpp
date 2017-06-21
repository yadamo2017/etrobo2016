/*
腕を動かすクラス
*/

#include "armControler.h"

#define P_GAIN  2.5F


ArmControler::ArmControler(
	ev3api::Motor* armMotor
	):
mArmMotor(armMotor){
	pwm = 0;
	forward = 60;
}

ArmControler::~ArmControler(){}

void ArmControler::armControl(int32_t deg){

	pwm = (deg - mArmMotor->getCount()) * P_GAIN;

	if(pwm>=forward){
		pwm = forward;
	}else if(pwm<-forward){
		pwm = -forward;
	}

	mArmMotor->setPWM(pwm);
}

void ArmControler::setForward(int _pwm){
	forward = _pwm;
}

