/*
まっすぐ走るクラス
*/



#include "straightRunner.h"



StraightRunner::StraightRunner(Driver* driver, Mileage* mileage){
	mDriver = driver;
	mMileage = mileage;
	pid = new Pid();
	forward = 0;
	pwm_l = forward;
	pwm_r = forward;


	enc_r = 0;
	enc_l = 0;

	buff_l = 0;
	buff_r = 0;

	firstFlag = false;
	count = 0;
}

StraightRunner::~StraightRunner(){}

void StraightRunner::straightRun(){

	if(firstFlag == false){
		buff_r = mMileage->mileageR();
		buff_l = mMileage->mileageL();
		firstFlag = true;
	}
	enc_r = mMileage->mileageR() - buff_r;
	enc_l = mMileage->mileageL() - buff_l;

	/*
	if((int)enc_l > (int)enc_r){
		if(pwm_r < 100) pwm_r++;
		else pwm_l--;
	}else if((int)enc_l < (int)enc_r){
		if(pwm_r < 100) pwm_l++;
		else pwm_r--;
	}
	*/

	//pwm_l = forward;
	//pwm_r = forward;

	pid->setGain(0.5, 0.01, 0);
	
	pwm_r = (int)pid->pidControl(enc_l - enc_r, 0);
	pwm_l = (int)pid->pidControl(enc_r - enc_l, 0);
	//mDriver->rotateR(forward);
	//mDriver->rotateL(forward);
	

	mDriver->rotateR(forward + pwm_r);
	mDriver->rotateL(forward + pwm_l);
	
	
	//buff_r = enc_r;
	//buff_l = enc_l;

}

void StraightRunner::setForward(int8_t _forward){
	//if(forward != _forward){
		forward = _forward;
		//pwm_l = forward;
		//pwm_r = forward;
		//buff_r = mMileage->mileageR();
		//buff_l = mMileage->mileageL();
	//}
}

void StraightRunner::reset(){
	firstFlag = false;
	pid->reset();
}

void StraightRunner::stop(){
	pid->reset();
	if(forward > 0) forward-=0.5;
	else if(forward < 0) forward+=0.5;
	else forward = 0;

	mDriver->setCommand(forward,0);
	
}
