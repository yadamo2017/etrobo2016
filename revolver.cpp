/*
指定された角度の旋回を行うクラス
*/

#include "revolver.h"
#include <math.h>

#define TYRE    82
#define OFFSET  ((TYRE*M_PI/4)-12)

Revolver::Revolver(
	Driver* driver,
	Mileage* mileage
	){
		mDriver = driver;
		mMileage = mileage;
		forward = 0;
		mile_l = 0;
		mile_r = 0;
		firstFlag = false;
		secondFlag = false;
		pid = new Pid();

		buff_orientation = 0;
}
Revolver::~Revolver(){}

bool Revolver::revolve(double angle){
	if(!firstFlag){
		mile_l = mMileage->mileageL();
		mile_r = mMileage->mileageR();
		firstFlag = true;
	}

	ang_r = mMileage->mileageR() - mile_r;
	ang_l = mMileage->mileageL() - mile_l;

	pid->setGain(0.5, 0.001, 0);

	if(forward == 0){
		if(angle > 0){
			if(ang_l - ang_r < TYRE*M_PI*(angle/90) - OFFSET*(angle/90)){
				pwm_r = pid->pidControl(ang_r + ang_l, 0);
				pwm_l = pid->pidControl(ang_r + ang_l, 0);

				mDriver->rotateL(forward - pwm_l +20);
				mDriver->rotateR(forward + pwm_r -20);
				return false;
			}else{
				mDriver->setCommand(0,0);
				return true;
			}
		}else{
			if(ang_l - ang_r > TYRE*M_PI*(angle/90) - OFFSET*(angle/90)){
				pwm_r = pid->pidControl(ang_r + ang_l, 0);
				pwm_l = pid->pidControl(ang_r + ang_l, 0);

				mDriver->rotateR(forward - pwm_r +20);
				mDriver->rotateL(forward + pwm_l -20);
				return false;
			}else{
				mDriver->setCommand(0,0);
				return true;
			}
		}
	}else{
		if(angle > 0){
			if(ang_l - ang_r < TYRE*M_PI*(angle/90) - OFFSET*(angle/90)){
				//pwm_r = pid->pidControl(ang_r + ang_l, 0);
				//pwm_l = pid->pidControl(ang_r + ang_l, 0);

				mDriver->rotateL(forward +15);
				mDriver->rotateR(forward -15);
				return false;
			}else{
				mDriver->setCommand(0,0);
				return true;
			}
		}else{
			if(ang_l - ang_r > TYRE*M_PI*(angle/90) - OFFSET*(angle/90)){
				//pwm_r = pid->pidControl(ang_r + ang_l, 0);
				//pwm_l = pid->pidControl(ang_r + ang_l, 0);

				mDriver->rotateR(forward +15);
				mDriver->rotateL(forward -15);
				return false;
			}else{
				mDriver->setCommand(0,0);
				return true;
			}
		}
	}

	return false;

}

void Revolver::setForward(int _forward){
	if(forward != _forward){
		forward = _forward;
	}
}

void Revolver::reset(){
	firstFlag = false;
	secondFlag = false;
	pid->reset();
}

bool Revolver::toRevolve(int orientation){
	int now = mMileage->orientation();

	if(!secondFlag){
		buff_orientation = now;
		secondFlag = true;
	}

	if(orientation - buff_orientation <= 6){
		if(orientation != now){
			this->revolve(180);
		}else{
			mDriver->setCommand(0,0);
			return true;
		}
	}else{
		if(orientation != now){
			this->revolve(-180);
		}else{
			mDriver->setCommand(0,0);
			return true;
		}
	}
	return false;
}