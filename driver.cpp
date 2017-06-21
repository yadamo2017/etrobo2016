/*
基本的な走行パターンを書くクラス
ライントレースなどのクラスから呼び出され命令に応じて走行するイメージ
*/

#include "driver.h"


Driver::Driver(
	ev3api::Motor* rightMotor,
	ev3api::Motor* leftMotor,
	Logger* logger
	):
mRightMotor(rightMotor),
	mLeftMotor(leftMotor) {
		mLogger = logger;

		motorEncR = 0;
		motorEncL = 0;
		buffR = 0;
		buffL = 0;

		forward = 0;
}

Driver::~Driver(){}


/*
操作に応じて動く
*/
void Driver::setCommand(int _forward, int turn){

	if(forward > _forward){
		forward--;
	}else if(forward < _forward){
		forward++;
	}

	rotateR(forward+turn);
	rotateL(forward-turn);
}


/*
指定したpwmでモータを動かす
*/
void Driver::rotateR(int pwmR){
	motorEncR = mRightMotor->getCount();

	mRightMotor->setPWM(pwmR);

	//mLogger->addData(motorEncR);

	buffR = motorEncR;
}

void Driver::rotateL(int pwmL){
	motorEncL = mLeftMotor->getCount();

	mLeftMotor->setPWM(pwmL);

	//mLogger->addData(motorEncL);

	buffL = motorEncL;
}
