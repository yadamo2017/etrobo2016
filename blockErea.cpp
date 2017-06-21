/*
ブロック並べエリアを走行するクラス
*/
#include "blockErea.h"

#define RED         0
#define GREEN       1
#define BLUE        2
#define YELLOW      3
#define BLACK	    4
#define Undecided   20
#define RIGHT_EDGE  0
#define LEFT_EDGE   1

#define STOP_TIME	100

#define abs(a) ((a) < 0 ? -(a) : (a))

Map mapInit(int x, int y, char color, bool flag);

BlockErea::BlockErea(
	StraightRunner* straightRunner,
	Mileage* mileage,
	Revolver* revolver,
	Tracer* tracer,
	ArmControler* armControler,
	ColorMonitor* colorMonitor,
	LineMonitor* lineMonitor,
	ReturnLine* returnLine,
	Logger* logger
	){
		mStraightRunner = straightRunner;
		mMileage = mileage;
		mRevolver = revolver;
		mTracer = tracer;
		mArmControler = armControler;
		mColorMonitor = colorMonitor;
		mLineMonitor = lineMonitor;
		mReturnLine = returnLine;
		mLogger = logger;

		superBlock = mapInit(1, 1, GREEN, false);
		block[0] = mapInit(2, 2, Undecided, false);
		block[1] = mapInit(0, 2, Undecided, false);
		block[2] = mapInit(3, 0, Undecided, false);

		gool = mapInit(0, 0, Undecided, false);


		fase = 0;


		lineCount = 0;
		timeCount = 0;
		bright = 0;
		brightBuff = 0;

		angle = 0;

		isFirstFlag = false;
		circleCatchInit = false;
		blockCatchInit = false;
		blockJudgeInit = false;

		mile = 0;

		status = new Status();



		ccFase = -1;
		bcFase = 0;
		bjFase = -1;

		turn = 0;

		firstTurn = 0;
		secondTurn = 0;
		goNum = 0;
		direction = 0;

		runFase = 0;

		colorCount = 0;

		patternInit = false;
		lineCounterInit = false;

		carryBlock = 0;

		loopCount = 0;


		endLineCountX = 0;
		endLineCountY = 0;

		blackCount = 0;


}
BlockErea::~BlockErea(){}

bool BlockErea::run(){
	if(!isFirstFlag){
		mile_l = mMileage->mileageL();
		mile_r = mMileage->mileageR();
		fase = 0;
		isFirstFlag = true;
	}

	//mLogger->addData(status->x);
	//mLogger->addData(status->y);
	//mLogger->addData(gool.x);
	//mLogger->addData(gool.y);
	//mLogger->addData(superBlock.x);
	//mLogger->addData(superBlock.y);
	//mLogger->addData(carryBlock);

	mile = mMileage->getMileage() - (mile_l+mile_r)/2; 

	mArmControler->armControl(angle);

	//mLogger->addData(fase);

	//mLogger->addData(bright);
	//mLogger->addData(brightBuff);


	switch(fase){
	case 0:
		mTracer->setCommand(30,0);
		mTracer->setEdge(1);
		mTracer->run();
		//mStraightRunner->setForward(30);
		//mStraightRunner->straightRun();
		if(mile > 500){
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			fase = 1;
		}
		break;
	case 1:
		if(timeCount < 99){
			timeCount++;
			mTracer->stop();
		}else if(mRevolver->revolve(-86)){
			timeCount = 0;
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			fase = 2;
		}
		break;

	case 2:
		timeCount++;
		if(timeCount < STOP_TIME) mTracer->stop();
		else{
			mStraightRunner->setForward(50);
			mStraightRunner->straightRun();
			if(mile > 370){
				mStraightRunner->setForward(0);
				mile_l= mMileage->mileageL();
				mile_r= mMileage->mileageR();
				mRevolver->reset();
				mStraightRunner->reset();
				timeCount=0;
				fase = 3;
			}
		}
		break;



	case 3:
		mStraightRunner->setForward(50);
		mStraightRunner->straightRun();
		if(superBlock.color!=BLACK){
			if(superBlock.x != 0){
				if(this->lineCounter(superBlock.x)){
					mile_l= mMileage->mileageL();
					mile_r= mMileage->mileageR();
					mRevolver->reset();
					mStraightRunner->reset();
					lineCount = 0;
					timeCount = 0;
					fase = 4;
				}
			}else{
				if(this->lineCounter(1)){
					mile_l= mMileage->mileageL();
					mile_r= mMileage->mileageR();
					mRevolver->reset();
					mStraightRunner->reset();
					lineCount = 0;
					timeCount = 0;
					if(superBlock.y == 1||superBlock.y==2) fase = 20;
					else fase = 4;
				}
			}
		}else{
			if(block[0].x != 0){
				if(this->lineCounter(block[0].x)){
					mile_l= mMileage->mileageL();
					mile_r= mMileage->mileageR();
					mRevolver->reset();
					mStraightRunner->reset();
					lineCount = 0;
					timeCount = 0;
					fase = 4;
				}
			}else{
				if(this->lineCounter(1)){
					mile_l= mMileage->mileageL();
					mile_r= mMileage->mileageR();
					mRevolver->reset();
					mStraightRunner->reset();
					lineCount = 0;
					timeCount = 0;
					if(block[0].y==1||block[0].y==2) fase =20;
					else fase = 4;
				}
			}
		}
		break;


	case 4:

		mStraightRunner->setForward(50);
		mStraightRunner->straightRun();
		if(mile > 250){
			mStraightRunner->setForward(0);
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			timeCount=0;
			fase = 5;
		}

		break;


	case 5:


		if(timeCount<STOP_TIME){
			timeCount++;
			mTracer->stop();
		}else{
			if(superBlock.color!=BLACK){
				if(superBlock.y <= 1){
					if(mRevolver->revolve(-90)){
						timeCount = 0;
						mRevolver->reset();
						mStraightRunner->reset();
						mile_l= mMileage->mileageL();
						mile_r= mMileage->mileageR();
						fase = 6;
					}
				}else if(superBlock.y >= 2){
					if(mRevolver->revolve(90)){
						timeCount = 0;
						mile_l= mMileage->mileageL();
						mile_r= mMileage->mileageR();
						mRevolver->reset();
						mStraightRunner->reset();
						fase = 6;
					}
				}
			}
			else{
				if(block[0].y <= 1){
					if(mRevolver->revolve(-90)){
						timeCount = 0;
						mRevolver->reset();
						mStraightRunner->reset();
						mile_l= mMileage->mileageL();
						mile_r= mMileage->mileageR();
						fase = 6;
					}
				}else if(block[0].y >= 2){
					if(mRevolver->revolve(90)){
						timeCount = 0;
						mile_l= mMileage->mileageL();
						mile_r= mMileage->mileageR();
						mRevolver->reset();
						mStraightRunner->reset();
						fase = 6;
					}
				}

			}
		}


		break;

	case 6:
		timeCount++;
		if(timeCount<STOP_TIME) mTracer->stop();
		else{
			timeCount = 0;
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			fase = 7;
		}
		break;


	case 7:
		mStraightRunner->setForward(50);
		mStraightRunner->straightRun();
		if(superBlock.color!=BLACK){
			if(superBlock.y==0||superBlock.y==3){
				if(this->lineCounter(2)){
					//if(this->lineCounter(abs(1))){
					mile_l= mMileage->mileageL();
					mile_r= mMileage->mileageR();
					mRevolver->reset();
					mStraightRunner->reset();
					lineCount = 0;
					timeCount = 0;
					fase = 20;
				}
			}else{
				if(this->lineCounter(1)){
					//if(this->lineCounter(abs(1))){
					mile_l= mMileage->mileageL();
					mile_r= mMileage->mileageR();
					mRevolver->reset();
					mStraightRunner->reset();
					lineCount = 0;
					timeCount = 0;
					fase = 20;
				}
			}
		}else{
			if(block[0].y==0||block[0].y==3){
				if(this->lineCounter(2)){
					//if(this->lineCounter(abs(1))){
					mile_l= mMileage->mileageL();
					mile_r= mMileage->mileageR();
					mRevolver->reset();
					mStraightRunner->reset();
					lineCount = 0;
					timeCount = 0;
					fase = 20;
				}
			}else{
				if(this->lineCounter(1)){
					//if(this->lineCounter(abs(1))){
					mile_l= mMileage->mileageL();
					mile_r= mMileage->mileageR();
					mRevolver->reset();
					mStraightRunner->reset();
					lineCount = 0;
					timeCount = 0;
					fase = 20;
				}
			}

		}
		break;


		/*
		case 8:

		mStraightRunner->setForward(40);
		mStraightRunner->straightRun();
		if(mile > 250){
		mStraightRunner->setForward(0);
		mile_l= mMileage->mileageL();
		mile_r= mMileage->mileageR();
		mRevolver->reset();
		mStraightRunner->reset();
		timeCount=0;
		fase = 20;
		}

		break;


		case 10:
		if(timeCount < 200){
		timeCount++;
		mTracer->stop();
		}else{
		if(superBlock.y == 0){
		if(mRevolver->revolve(90)){
		timeCount = 0;
		mRevolver->reset();
		mile_l= mMileage->mileageL();
		mile_r= mMileage->mileageR();
		mStraightRunner->reset();
		fase = 12;
		}
		}else if(superBlock.y == 3){
		if(mRevolver->revolve(-90)){
		timeCount = 0;
		mile_l= mMileage->mileageL();
		mile_r= mMileage->mileageR();
		mRevolver->reset();
		mStraightRunner->reset();
		fase = 12;
		}
		}
		}
		break;


		case 12:
		if(timeCount <200){
		timeCount++;
		mTracer->stop();
		}else{
		timeCount = 0;
		mile_l= mMileage->mileageL();
		mile_r= mMileage->mileageR();
		mRevolver->reset();
		mStraightRunner->reset();
		fase = 15;
		}
		break;


		case 15:
		mStraightRunner->setForward(40);
		mStraightRunner->straightRun();
		if(this->lineCounter(superBlock.x)){
		mile_l= mMileage->mileageL();
		mile_r= mMileage->mileageR();
		mRevolver->reset();
		mStraightRunner->reset();
		lineCount = 0;
		timeCount = 0;
		fase = 20;
		}
		break;
		*/


	case 20:
		if(superBlock.color!=BLACK){
			if(superBlock.y <= 1){
				if(superBlock.x != 0) turn = 1;
				else turn = -1;

			}else{
				if(superBlock.x != 0) turn = -1;
				else turn = 1;
			}
		}else{
			if(block[0].y <= 1){
				if(block[0].x != 0) turn = 1;
				else turn = -1;

			}else{
				if(block[0].x != 0) turn = -1;
				else turn = 1;
			}
		}
		if(mReturnLine->lineReturn(turn)){
			if(turn <0) mTracer->setEdge(RIGHT_EDGE);
			else mTracer->setEdge(LEFT_EDGE);
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			if(superBlock.color!=BLACK) fase = 40;
			else fase = 70;
		}

		break;

		/*
		case 30:
		mTracer->setCommand(20,0);
		mTracer->run();
		if(mile>100){
		mile_l= mMileage->mileageL();
		mile_r= mMileage->mileageR();
		mRevolver->reset();
		mStraightRunner->reset();
		fase = 40;
		timeCount = 0;	
		}

		break;
		*/


	case 40:
		if(this->blockCatch()){
			timeCount = 0;
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			fase = 45;
			status->setStatus(mMileage->orientation(), superBlock.x, superBlock.y);
			gool = this->calcSetPlace(superBlock.color, status);

			//mLogger->addData(gool.x);
			//mLogger->addData(gool.y);
		}
		break;

	case 45:
		if(this->patternRun(status, gool)){
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			timeCount = 0;
			lineCount = 0;
			fase = 46;
		}
		break;

	case 46:
		if(this->circleCatch()){
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			lineCount = 0;
			circleCatchInit = false;
			fase = 50;
		}
		break;


	case 50:
		timeCount++;
		if(timeCount<STOP_TIME){
			mTracer->stop();
		}else{
			mStraightRunner->setForward(-20);
			mStraightRunner->straightRun();
			if(mile < -100){
				mile_l= mMileage->mileageL();
				mile_r= mMileage->mileageR();
				mRevolver->reset();
				mStraightRunner->reset();
				timeCount = 0;
				lineCount = 0;
				fase = 55;
			}
		}
		break;



	case 55:

		if(mRevolver->revolve(180)){
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			timeCount = 0;
			lineCount = 0;
			mTracer->setEdge(LEFT_EDGE);
			if(loopCount == 0 && superBlock.color!=BLACK){
				superBlock = mapInit(gool.x, gool.y, superBlock.color, true);
			}else{
				block[carryBlock] = mapInit(gool.x, gool.y, block[carryBlock].color, true);
			}
			status->setStatus(mMileage->orientation(), gool.x, gool.y);
			gool = this->nextPlace(status);

			if(loopCount <= 1){
				fase = 56;
				loopCount++;
			}
			else{
				fase = 196;
				loopCount = 0;
			}
		}

		break;

	case 56:
		timeCount++;
		if(timeCount<STOP_TIME) mTracer->stop();
		else{
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			timeCount = 0;
			lineCount = 0;
			fase = 60;
		}
		break;

	case 60:
		if(this->patternRun(status, gool)){
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			timeCount = 0;
			lineCount = 0;
			if(gool.y==0 && mMileage->orientation()<=7 && mMileage->orientation()>=5) fase = 61;
			else fase = 70;
		}
		break;

	case 61:

		if(gool.x == 3) turn = -1;
		else turn = 1;
		if(mRevolver->revolve(90*turn)){
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			lineCount = 0;
			timeCount = 0;
			fase = 62;
		}

		break;

	case 62:
		timeCount++;
		if(timeCount<STOP_TIME) mTracer->stop();
		else{
			mStraightRunner->setForward(50);
			mStraightRunner->straightRun();
			if(mile>200){
				mile_l= mMileage->mileageL();
				mile_r= mMileage->mileageR();
				mRevolver->reset();
				mStraightRunner->reset();
				lineCount = 0;
				timeCount = 0;
				fase = 63;
			}
		}
		break;

	case 63:
		timeCount++;
		if(timeCount<STOP_TIME){
			mTracer->stop();
		}else{
			if(mRevolver->revolve(90*turn*(-1))){
				mile_l= mMileage->mileageL();
				mile_r= mMileage->mileageR();
				mRevolver->reset();
				mStraightRunner->reset();
				lineCount = 0;
				timeCount = 0;
				fase = 64;
			}
		}
		break;



	case 64:
		timeCount++;
		if(timeCount<STOP_TIME){
			mTracer->stop();
		}else{
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			lineCount = 0;
			timeCount = 0;
			fase = 65;
		}
		break;

	case 65:
		mStraightRunner->setForward(50);
		mStraightRunner->straightRun();
		if(this->lineCounter(1)){
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			lineCount = 0;
			timeCount = 0;

			fase = 66;
		}
		break;

	case 66:
		if(mReturnLine->lineReturn(-turn)){
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			if(-turn == 1) mTracer->setEdge(1);
			else mTracer->setEdge(0);
			lineCount = 0;
			timeCount = 0;

			fase = 70;

		}
		break;


	case 70:
		if(this->blockJudge()){
			timeCount = 0;
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			if(superBlock.color==BLACK && loopCount==0){
				carryBlock = 0;
				gool = mapInit(block[0].x, block[0].y, block[0].color, false);
			}
			status->setStatus(mMileage->orientation(), gool.x, gool.y);
			if(block[carryBlock].color!=4){
				gool = this->calcSetPlace(block[carryBlock].color, status);
				fase = 45;
			}
			else{
				if(blackCount == 0) loopCount--;
				blackCount++;
				fase = 50;
			}

			//mLogger->addData(block[carryBlock].color);
		}
		break;


	case 196:
		timeCount++;
		if(timeCount<STOP_TIME) mTracer->stop();
		else{
			if(mLineMonitor->checkBrightness() > 10){
				if(mRevolver->revolve(-60)){
					mile_l= mMileage->mileageL();
					mile_r= mMileage->mileageR();
					mRevolver->reset();
					mStraightRunner->reset();
					lineCount = 0;
					timeCount = 0;
					if(loopCount == 0){
						fase = 197;
						loopCount++;
					}else fase = 200;

				}
			}else{
				mile_l= mMileage->mileageL();
				mile_r= mMileage->mileageR();
				mRevolver->reset();
				mStraightRunner->reset();
				lineCount = 0;
				timeCount = 0;
				mTracer->setEdge(RIGHT_EDGE);
				fase = 198;
			}
		}
		break;

	case 197:

		if(mLineMonitor->checkBrightness() > 10){
			if(mRevolver->revolve(120)){
				mile_l= mMileage->mileageL();
				mile_r= mMileage->mileageR();
				mRevolver->reset();
				mStraightRunner->reset();
				lineCount = 0;
				timeCount = 0;
				fase = 196;
			}
		}else{
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			lineCount = 0;
			timeCount = 0;
			mTracer->setEdge(LEFT_EDGE);
			fase = 198;
		}

		break;

	case 198:
		mTracer->setCommand(15, 0);
		mTracer->run();
		if(mile > 50){
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			lineCount = 0;
			timeCount = 0;
			fase = 199;
		}
		break;

	case 199:
		timeCount++;
		if(timeCount > STOP_TIME){
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			lineCount = 0;
			timeCount = 0;
			fase = 200;
		}
		break;

	case 200:
		if((mMileage->orientation()<=10 && mMileage->orientation()>=8)){
			fase = 205;
			endLineCountX = abs(status->x-3);
			endLineCountY = abs(status->y-3)-1;
		}else if(mMileage->orientation()<=4 && mMileage->orientation()>=2){
			fase = 205;
			endLineCountX = abs(status->x-3) + 1;
			endLineCountY = abs(status->y-3)-1;
		}else{
			if(status->x==3) endLineCountX = abs(status->x-3)+1;
			else endLineCountX = abs(status->x-3);

			if(mMileage->orientation()<=7 && mMileage->orientation()>=5) endLineCountY = abs(status->y-3);
			else if(mMileage->orientation() == 12 || mMileage->orientation()==0 
				|| mMileage->orientation()==1 || mMileage->orientation()==11) endLineCountY = abs(status->y-3)-1;

			fase = 201;
		}

		break;


	case 201:
		if((mMileage->orientation()>=3 && mMileage->orientation()<=9)){
			if(status->x!=3) turn = 1;
			else turn = -1;
		}else{
			if(status->x!=3) turn = -1;
			else turn = 1;
		}
		timeCount++;
		if(timeCount<STOP_TIME){
			mTracer->stop();
		}else{

			timeCount = 0;
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			fase = 202;

		}
		break;

	case 202:
		if(mRevolver->revolve(90*turn)){
			timeCount = 0;
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			fase = 203;
		}
		break;

	case 203:
		timeCount++;
		if(timeCount<STOP_TIME) mTracer->stop();
		else{
			mStraightRunner->setForward(50);
			mStraightRunner->straightRun();
			if(mile>200){
				timeCount = 0;
				mile_l= mMileage->mileageL();
				mile_r= mMileage->mileageR();
				mRevolver->reset();
				mStraightRunner->reset();
				fase = 205;
			}
		}
		break;

	case 205:
		if(mMileage->orientation()<=6){
			if(status->y!=3) turn = -1;
			else turn = 1;
		}else{
			if(status->y!=3) turn = 1;
			else turn = -1;
		}



		timeCount = 0;
		mile_l= mMileage->mileageL();
		mile_r= mMileage->mileageR();
		mRevolver->reset();
		mStraightRunner->reset();
		fase = 206;


		break;

	case 206:
		timeCount++;
		if(timeCount<STOP_TIME) mTracer->stop();
		else{
			if(mRevolver->revolve(90*turn)){
				timeCount = 0;
				mile_l= mMileage->mileageL();
				mile_r= mMileage->mileageR();
				mRevolver->reset();
				mStraightRunner->reset();
				fase = 207;
			}
		}

		break;

	case 207:
		if(timeCount<STOP_TIME){
			timeCount++;
			mTracer->stop();
		}else{

			timeCount = 0;
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			fase = 208;

		}
		break;

	case 208:
		mStraightRunner->setForward(50);
		mStraightRunner->straightRun();
		if(mile > 30){
			timeCount = 0;
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			if(status->y != 3) fase = 209;
			else fase = 210;
		}
		break;

	case 209:
		mStraightRunner->setForward(50);
		mStraightRunner->straightRun();
		if(this->lineCounter(endLineCountY)){
			timeCount = 0;
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			fase = 210;
		}
		break;

	case 210:
		mStraightRunner->setForward(50);
		mStraightRunner->straightRun();
		if(mile > 250){
			timeCount = 0;
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			fase = 211;
		}
		break;


	case 211:
		timeCount++;
		if(timeCount<STOP_TIME){
			mTracer->stop();
		}else{
			if(mMileage->orientation()<=7 && mMileage->orientation()>=5){
				turn = 1;
			}else{
				turn = -1;
			}

			fase = 212;
		}
		break;

	case 212:
		if(mRevolver->revolve(90*turn)){
			timeCount = 0;
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			lineCount=0;
			fase = 213;
		}
		break;

	case 213:
		timeCount++;
		if(timeCount<STOP_TIME) mTracer->stop();
		else{
			timeCount = 0;
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			lineCount=0;
			fase = 214;

		}
		break;

	case 214:
		mStraightRunner->setForward(50);
		mStraightRunner->straightRun();
		if(this->lineCounter(endLineCountX)){
			timeCount = 0;
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			fase = 215;
		}
		break;


	case 215:
		mStraightRunner->setForward(50);
		mStraightRunner->straightRun();
		if(mile>50){
			timeCount = 0;
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			lineCount=0;
			fase = 220;
		}
		break;

	case 220:
		mStraightRunner->setForward(50);
		mStraightRunner->straightRun();
		if(this->lineCounter(1)){
			timeCount = 0;
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			lineCount=0;
			fase = 225;
		}

		break;

	case 225:
		if(timeCount<STOP_TIME){
			timeCount++;
			mTracer->stop();
		}else{
			if(mReturnLine->lineReturn(1)){
				mile_l= mMileage->mileageL();
				mile_r= mMileage->mileageR();
				mRevolver->reset();
				mStraightRunner->reset();
				lineCount = 0;
				timeCount=0;
				fase = 240;
			}

		}
		break;

	case 240:
		mTracer->setEdge(LEFT_EDGE);
		mTracer->setCommand(30,0);
		mTracer->run();
		if(mile>600){
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			lineCount = 0;
			timeCount=0;
			fase = 255;
		}
		break;

	case 255:
		//mStraightRunner->setForward(0);
		//mStraightRunner->straightRun();
		//mTracer->stop();
		return true;
		break;


	}

	return false;

}

Map mapInit(int x, int y, char color, bool flag){
	Map i = {x, y, color, flag};
	return i;
}

bool BlockErea::circleCatch(){

	if(!circleCatchInit){
		ccFase = -1;
		colorCount = 0;
		timeCount = 0;
		circleCatchInit = true;
	}

	switch(ccFase){


	case -1:
		mTracer->setMode(1);
		mTracer->setCommand(10,0);
		mTracer->run();
		if(mile>10){
			colorCount = 0;
			timeCount = 0;
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mStraightRunner->reset();
			mRevolver->reset();
			ccFase++;
		}
		break;

	case 0:
		if(colorCount ==0){
			mTracer->setMode(1);
			mTracer->setCommand(10, 0);
			mTracer->run();
		}else{
			mStraightRunner->setForward(10);
			mStraightRunner->straightRun();
		}
		mColorMonitor->checkColor(color);
		if(mColorMonitor->colorJudge2(color,0)!=10 && mColorMonitor->colorJudge2(color,0)!=4) colorCount++;
		else colorCount = 0;
		if(colorCount > 5){
			colorCount = 0;
			timeCount = 0;
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mStraightRunner->reset();
			mRevolver->reset();
			mTracer->reset();
			ccFase++;
		}
		break;

	case 1:
		timeCount++;
		if(timeCount < 99){
			mTracer->stop();
		}else{
			timeCount = 0;
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();

			ccFase++;
		}
		break;

	case 2:
		circleCatchInit = false;
		return true;
		break;
	}

	return false;
}

bool BlockErea::blockCatch(){

	if(!blockCatchInit){
		bcFase = 0;
		timeCount = 0;
		mile_l= mMileage->mileageL();
		mile_r= mMileage->mileageR();
		blockCatchInit = true;
	}

	switch(bcFase){
	case 0:
		if(this->circleCatch()){
			bcFase++;
			timeCount = 0;
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mStraightRunner->reset();
			mRevolver->reset();
		}
		break;
	case 1:
		mStraightRunner->setForward(20);
		mStraightRunner->straightRun();
		if(mile > 150){
			angle = 0;
			timeCount = 0;
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			bcFase++;
		}
		break;
	case 2:
		timeCount++;
		if(timeCount<0){
			mTracer->stop();
		}else{
			timeCount = 0;
			blockCatchInit = false;
			status->setStatus(mMileage->orientation(), superBlock.x, superBlock.y);
			return true;
			break;
		}
	}
	return false;
}



bool BlockErea::blockJudge(){

	int blockC;

	if(!blockJudgeInit){
		bjFase = -1;
		timeCount = 0;
		mile_l= mMileage->mileageL();
		mile_r= mMileage->mileageR();
		blockC = 10;
		blockJudgeInit = true;
	}

	switch(bjFase){
	case -1:
		if(this->circleCatch()){
			bjFase++;
			timeCount = 0;
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mStraightRunner->reset();
			mRevolver->reset();
		}
		break;
	case 0:
		mStraightRunner->setForward(20);
		mStraightRunner->straightRun();
		if(mile>10){
			bjFase++;
			timeCount = 0;
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mStraightRunner->reset();
			mRevolver->reset();
		}
		break;
	case 1:
		mStraightRunner->setForward(-20);
		mStraightRunner->straightRun();
		if(mile < -25){
			timeCount = 0;
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			bjFase++;
		}
		break;

	case 2:
		timeCount++;
		if(timeCount<500){
			mTracer->stop();
			//mArmControler->armControl(60);
			mArmControler->setForward(10);
			angle = 68;
		}else{
			timeCount = 0;
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			mStraightRunner->setForward(0);
			bjFase++;
		}

		break;

	case 3:
		mColorMonitor->checkColor(color);
		blockC = mColorMonitor->colorJudge2(color, 1);
		mStraightRunner->straightRun();
		if(blockC==10){
			ev3_speaker_play_tone(NOTE_G4, 2);
			timeCount++;
			if(timeCount<100){
				mStraightRunner->setForward(-10);
			}else if(timeCount<200){
				mStraightRunner->setForward(10);
			}else timeCount = 0;
		}else{
			mArmControler->setForward(60);
			angle = 0;
			timeCount = 0;
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			block[carryBlock].color = blockC;
			if(blockC==4){
				bjFase = 60;
			}else bjFase = 4;
		}
		break;

	case 4:
		mStraightRunner->setForward(20);
		mStraightRunner->straightRun();
		if(mile > 150){
			angle = 0;
			timeCount = 0;
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			bjFase = 60;
		}
		break;



	case 60:
		timeCount++;
		if(timeCount<0){
			mTracer->stop();
		}else{
			blockJudgeInit = false;
			timeCount = 0;
			return true;
			break;
		}
	}


	return false;
}


Map BlockErea::calcSetPlace(int blockColor, Status* status){

	Map setable[4];

	for(int i=0; i<4; i++){
		setable[i].x = 15;
		setable[i].y = 15;
	}

	if(blockColor==0){
		for(int i=0; i<2; i++){
			for(int k=0; k<2; k++){
				if(i==0){
					if((i==superBlock.x&&k+2==superBlock.y) || (i==block[0].x&&k+2==block[0].y) || (i==block[1].x&&k+2==block[1].y) || (i==block[2].x&&k+2==block[2].y)){
						setable[i+k] = mapInit(10,10,Undecided,false);
					}else setable[i+k] = mapInit(i,k+2,Undecided,false);
				}else{
					if((i==superBlock.x&&k+2==superBlock.y) || (i==block[0].x&&k+2==block[0].y) || (i==block[1].x&&k+2==block[1].y) || (i==block[2].x&&k+2==block[2].y)){
						setable[i+k+1] = mapInit(10,10,Undecided,false);
					}else setable[i+k+1] = mapInit(i,k+2,Undecided,false);
				}
			}		
		}
	}else if(blockColor==1){
		for(int i=0; i<2; i++){
			for(int k=0; k<2; k++){
				if(i==0){
					if((i+2==superBlock.x&&k==superBlock.y) || (i+2==block[0].x&&k==block[0].y) || (i+2==block[1].x&&k==block[1].y) || (i+2==block[2].x&&k==block[2].y)){
						setable[i+k] = mapInit(10,10,Undecided,false);
					}else setable[i+k] = mapInit(i+2,k,Undecided,false);
				}else{
					if((i+2==superBlock.x&&k==superBlock.y) || (i+2==block[0].x&&k==block[0].y) || (i+2==block[1].x&&k==block[1].y) || (i+2==block[2].x&&k==block[2].y)){
						setable[i+k+1] = mapInit(10,10,Undecided,false);
					}else setable[i+k+1] = mapInit(i+2,k,Undecided,false);
				}
			}		
		}
	}else if(blockColor==2){
		for(int i=0; i<2; i++){
			for(int k=0; k<2; k++){
				if(i==0){
					if((i+2==superBlock.x&&k+2==superBlock.y) || (i+2==block[0].x&&k+2==block[0].y) || (i+2==block[1].x&&k+2==block[1].y) || (i+2==block[2].x&&k+2==block[2].y)){
						setable[i+k] = mapInit(10,10,Undecided,false);
					}else setable[i+k] = mapInit(i+2,k+2,Undecided,false);
				}else{
					if((i+2==superBlock.x&&k+2==superBlock.y) || (i+2==block[0].x&&k+2==block[0].y) || (i+2==block[1].x&&k+2==block[1].y) || (i+2==block[2].x&&k+2==block[2].y)){
						setable[i+k+1] = mapInit(10,10,Undecided,false);
					}else setable[i+k+1] = mapInit(i+2,k+2,Undecided,false);
				}
			}		
		}
	}else if(blockColor==3){
		for(int i=0; i<2; i++){
			for(int k=0; k<2; k++){
				if(i==0){
					if((i==superBlock.x&&k==superBlock.y) || (i==block[0].x&&k==block[0].y) || (i==block[1].x&&k==block[1].y) || (i==block[2].x&&k==block[2].y)){
						setable[i+k] = mapInit(10,10,Undecided,false);
					}else setable[i+k] = mapInit(i,k,Undecided,false);
				}else{
					if((i==superBlock.x&&k==superBlock.y) || (i==block[0].x&&k==block[0].y) || (i==block[1].x&&k==block[1].y) || (i==block[2].x&&k==block[2].y)){
						setable[i+k+1] = mapInit(10,10,Undecided,false);
					}else setable[i+k+1] = mapInit(i,k,Undecided,false);
				}
			}		
		}
	}
	/*
	for(int i=0; i<4; i++){
	mLogger->addData(setable[i].x);
	}
	*/

	//mLogger->addData(setable[0].x);
	//mLogger->addData(setable[0].y);

	int min;
	int min_i;
	int distance;

	for(int i=0; i<4; i++){
		distance = ((status->x-setable[i].x)*(status->x-setable[i].x))+((status->y-setable[i].y)*(status->y-setable[i].y));
		if(i==0){
			min = 200;
			min_i = 0;
		}
		if(min>distance){
			min = distance;
			min_i = i;
		}
	}

	//mLogger->addData(distance);

	return setable[min_i];

}

Map BlockErea::nextPlace(Status* status){
	int distance;
	int min;
	int min_i;

	for(int i=0; i<3; i++){
		distance = ((status->x-block[i].x)*(status->x-block[i].x))+((status->y-block[i].y)*(status->y-block[i].y));
		if(i==0){
			min = 200;
			min_i = 10;
		}
		if(!block[i].flag){
			if(min > distance){
				min = distance;
				min_i = i;
			}
		}
	}

	carryBlock = min_i;

	if(min_i == 10){
		Map finish = mapInit(10, 10, Undecided, true);
		return finish;
	}else{

		return block[min_i];
	}
}



bool BlockErea::patternRun(Status* status, Map gool){

	//mLogger->addData(goNum);
	//mLogger->addData(lineCount);
	//mLogger->addData(runFase);

	if(!patternInit){

		runFase = -3;
		firstTurn = 0;
		secondTurn = 0;
		thirdTurn = 0;
		goNum = 0;
		lineCount = 0;
		patternInit = true;
	}

	int firstForward = 0;

	if(status->orientation==0||status->orientation==1||status->orientation==11||status->orientation==12){
		if(status->y - gool.y > 0){
			if(status->x - gool.x < 0){
				firstTurn = -1;
				secondTurn = -1;
				thirdTurn = 1;
			}
			else if(status->x - gool.x > 0){
				firstTurn = 1;
				secondTurn = 1;
				thirdTurn = -1;
			}
			else{
				if(status->x==0){
					firstTurn = -1;
					secondTurn = -1;
					thirdTurn = -1;
				}
				else if(status->x == 3){
					firstTurn = 1;
					secondTurn = 1;
					thirdTurn = 1;
				}
				else{
					firstTurn = -1;
					secondTurn = -1;
					thirdTurn = -1;
				}
			}
			goNum = abs(status->y - gool.y)+1;

		}else if(status->y - gool.y < -1){
			if(status->x - gool.x < 0){
				firstTurn = -1;
				secondTurn = 1;
				thirdTurn = -1;
			}else if(status->x - gool.x >0){
				firstTurn = 1;
				secondTurn = -1;
				thirdTurn = 1;
			}else{
				if(status->x == 3){
					firstTurn = 1;
					secondTurn = -1;
					thirdTurn = -1;
				}else{
					firstTurn = -1;
					secondTurn = 1;
					thirdTurn = 1;
				}
			}
			goNum = abs(status->y - gool.y);
		}
		else{
			if(status->y!=3){
				if(status->x - gool.x < 0){
					firstTurn = -1;
					secondTurn = 0;
					if(status->y == gool.y) thirdTurn = -1;
					else thirdTurn = 1;
				}
				else if(status->x - gool.x > 0){
					firstTurn = 1;
					secondTurn = 0;
					if(status->y == gool.y) thirdTurn = 1;
					else thirdTurn = -1;
				}
				goNum = abs(status->x - gool.x);
			}
			else{
				if(status->x - gool.x < 0){
					firstTurn = -1;
					secondTurn = -1;
					thirdTurn = 1;
				}else{
					firstTurn = 1;
					secondTurn = 1;
					thirdTurn = -1;
				}
				goNum = 1;
			}
		}
		direction = 0;

	}else if(status->orientation<=4&&status->orientation>=2){
		if(status->x - gool.x < 0){
			if(status->y - gool.y < 0){
				firstTurn = -1;
				secondTurn = -1;
				thirdTurn = 1;
			}
			else if(status->y - gool.y > 0){
				firstTurn = 1;
				secondTurn = 1;
				thirdTurn = -1;
			}
			else{
				if(status->y==0) firstTurn = secondTurn = thirdTurn = -1;
				else if(status->y==3) firstTurn = secondTurn = thirdTurn = 1;
				else firstTurn = secondTurn = thirdTurn = -1;
			}
			goNum = abs(status->x - gool.x)+1;

		}else if(status->x - gool.x > 1){
			if(status->y - gool.y < 0){
				firstTurn = -1;
				secondTurn = 1;
				thirdTurn = -1;
			}else if(status->y - gool.y > 0){
				firstTurn = 1;
				secondTurn = -1;
				thirdTurn = 1;
			}else{
				if(status->y==3){
					firstTurn = 1;
					secondTurn = -1;
					thirdTurn = -1;
				}else{
					firstTurn = -1;
					secondTurn = 1;
					thirdTurn = 1;
				}
			}
			goNum = abs(status->x - gool.x);
		}
		else{
			if(status->x != 0){
				if(status->y - gool.y < 0){
					firstTurn = -1;
					secondTurn = 0;
					if(status->x == gool.x) thirdTurn = -1;
					else thirdTurn = 1;
				}
				else if(status->y - gool.y > 0){
					firstTurn = 1;
					secondTurn = 0;
					if(status->x == gool.x) thirdTurn = 1;
					else thirdTurn = -1;
				}
				goNum = abs(status->y - gool.y);
			}

			else{
				if(status->y - gool.y < 0){
					firstTurn = -1;
					secondTurn = -1;
					thirdTurn = 1;
				}else{
					firstTurn = 1;
					secondTurn = 1;
					thirdTurn = -1;
				}
				goNum = 1;


			}
		}
		direction = 1;


	}else if(status->orientation<=7&&status->orientation>=5){
		if(status->y - gool.y < 0){
			if(status->x - gool.x > 0){
				firstTurn = secondTurn = -1;
				thirdTurn = 1;
			}
			else if(status->x - gool.x < 0){
				firstTurn = secondTurn = 1;
				thirdTurn = -1;
			}
			else{
				if(status->x==0) firstTurn = secondTurn = thirdTurn = 1;
				else if(status->x == 3) firstTurn = secondTurn = thirdTurn = -1;
				else firstTurn = secondTurn = thirdTurn = 1;
			}
			goNum = abs(status->y - gool.y)+1;

		}else if(status->y - gool.y > 1){
			if(status->x - gool.x < 0){
				firstTurn = 1;
				secondTurn = -1;
				thirdTurn = 1;
			}else if(status->x - gool.x > 0){
				firstTurn = -1;
				secondTurn = 1;
				thirdTurn = -1;
			}else{
				if(status->x == 3){
					firstTurn = -1;
					secondTurn = 1;
					thirdTurn = 1;
				}else{
					firstTurn = 1;
					secondTurn = -1;
					thirdTurn = -1;
				}
			}
			goNum = abs(status->y - gool.y);
		}
		else{
			if(status->y != 0){
				if(status->x - gool.x < 0){
					firstTurn = 1;
					secondTurn = 0;
					if(status->y==gool.y) thirdTurn = 1;
					else thirdTurn = -1;
				}
				else if(status->x - gool.x > 0){
					firstTurn = -1;
					secondTurn = 0;
					if(status->y==gool.y) thirdTurn = -1;
					else thirdTurn = 1;
				}
				goNum = abs(status->x - gool.x);
			}
			else{

				if(status->x - gool.x > 0){
					firstTurn = -1;
					secondTurn = -1;
					thirdTurn = 1;
				}else{
					firstTurn = 1;
					secondTurn = 1;
					thirdTurn = -1;
				}
				goNum = 1;
			}

		}


		direction = 2;

	}else{
		if(status->x - gool.x > 0){
			if(status->y - gool.y > 0){
				firstTurn = secondTurn = -1;
				thirdTurn = 1;
			}
			else if(status->y - gool.y < 0){
				firstTurn = secondTurn = 1;
				thirdTurn = -1;
			}
			else{
				if(status->y==0) firstTurn = secondTurn = thirdTurn =1;
				else if(status->y==3) firstTurn = secondTurn = thirdTurn = -1;
				else firstTurn = secondTurn = thirdTurn = 1;
			}
			goNum = abs(status->x - gool.x)+1;

		}else if(status->x - gool.x < -1){
			if(status->y -gool.y > 0){
				firstTurn = -1;
				secondTurn = 1;
				thirdTurn = -1;
			}else if(status->y - gool.y < 0){
				firstTurn = 1;
				secondTurn = -1;
				thirdTurn = - 1;
			}else{
				if(status->y==3){
					firstTurn = -1;
					secondTurn = 1;
					thirdTurn = 1;
				}else{
					firstTurn = 1;
					secondTurn = -1;
					thirdTurn = -1;
				}
			}
			goNum = abs(status->x - gool.x);
		}
		else{
			if(status->x != 3){
				if(status->y - gool.y > 0){
					firstTurn = -1;
					secondTurn = 0;
					if(status->x==gool.x) thirdTurn = -1;
					else thirdTurn = 1;
				}
				else if(status->y - gool.y < 0){
					firstTurn = 1;
					secondTurn = 0;
					if(status->x==gool.x) thirdTurn = 1;
					else thirdTurn = -1;
				}
				goNum = abs(status->y - gool.y);
			}
			else{
				if(status->y - gool.y > 0){
					firstTurn = -1;
					secondTurn = -1;
					thirdTurn = 1;
				}else{
					firstTurn = 1;
					secondTurn = 1;
					thirdTurn = -1;
				}
				goNum = 1;
			}
		}

		direction = 3;
	}

	switch(runFase){

	case -3:
		mile_l= mMileage->mileageL();
		mile_r= mMileage->mileageR();
		mRevolver->reset();
		mStraightRunner->reset();
		lineCount = 0;
		timeCount=0;
		if(firstTurn!=0) runFase = -2;
		else runFase = 240;

		break;

	case -2:
		mStraightRunner->setForward(20);
		mStraightRunner->straightRun();
		if(mile > 50){
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			lineCount = 0;
			timeCount=0;
			runFase = -1;
		}
		break;

	case -1:
		timeCount++;
		if(timeCount<STOP_TIME) mTracer->stop();
		else{
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			lineCount = 0;
			timeCount=0;
			runFase = 0;
		}
		break;


	case 0:
		mRevolver->setForward(5);
		if(firstTurn == 1){
			if(mRevolver->revolve(93)){
				mile_l= mMileage->mileageL();
				mile_r= mMileage->mileageR();
				mRevolver->reset();
				mStraightRunner->reset();
				lineCount = 0;
				timeCount=0;
				if(secondTurn == 0) runFase = 100;
				else runFase = 2;
			}
		}else if(firstTurn == -1){
			if(mRevolver->revolve(-92)){
				mile_l= mMileage->mileageL();
				mile_r= mMileage->mileageR();
				mRevolver->reset();
				mStraightRunner->reset();
				lineCount = 0;
				timeCount=0;
				if(secondTurn == 0) runFase = 100;
				else runFase = 2;
			}
		}else{
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			lineCount = 0;
			timeCount=0;
			runFase = 240;		
		}
		break;

	case 2:
		if(timeCount < STOP_TIME){
			timeCount++;
			mTracer->stop();
		}else{
			mStraightRunner->setForward(40);
			mStraightRunner->straightRun();
			if(mile > 200){
				mile_l= mMileage->mileageL();
				mile_r= mMileage->mileageR();
				mRevolver->reset();
				mStraightRunner->reset();
				lineCount = 0;
				timeCount=0;
				if(direction == 0 || direction == 2){
					if((abs(status->x - gool.x)<=1)) runFase = 10;
					else runFase = 4;
				}else{
					if(abs(status->y - gool.y)<=1) runFase = 10;
					else runFase = 4;
				}

			}
		}
		break;

	case 4:

		mStraightRunner->setForward(40);
		mStraightRunner->straightRun();
		if(direction == 0 || direction == 2){
			if(abs(status->x - gool.x) == 2) firstForward = 400;
			else if(abs(status->x - gool.x)==3) firstForward = 900;
			if(mile > firstForward){
				mile_l= mMileage->mileageL();
				mile_r= mMileage->mileageR();
				mRevolver->reset();
				mStraightRunner->reset();
				lineCount = 0;
				timeCount=0;
				runFase = 10;
			}
		}else{
			if(abs(status->y - gool.y) == 2) firstForward = 400;
			else if(abs(status->y - gool.y)==3) firstForward = 900;
			if(mile > firstForward){
				mile_l= mMileage->mileageL();
				mile_r= mMileage->mileageR();
				mRevolver->reset();
				mStraightRunner->reset();
				lineCount = 0;
				timeCount=0;
				runFase = 10;
			}
		}

		break;

	case 10:
		if(timeCount<STOP_TIME){
			timeCount++;
			mTracer->stop();
		}else{
			if(secondTurn == 1){
				if(mRevolver->revolve(92)){
					mile_l= mMileage->mileageL();
					mile_r= mMileage->mileageR();
					mRevolver->reset();
					mStraightRunner->reset();
					lineCount = 0;
					timeCount=0;
					runFase = 100;
				}
			}else if(secondTurn == -1){
				if(mRevolver->revolve(-92)){
					mile_l= mMileage->mileageL();
					mile_r= mMileage->mileageR();
					mRevolver->reset();
					mStraightRunner->reset();
					lineCount = 0;
					timeCount=0;
					runFase = 100;
				}
			}else{
				mile_l= mMileage->mileageL();
				mile_r= mMileage->mileageR();
				mRevolver->reset();
				mStraightRunner->reset();
				lineCount = 0;
				timeCount=0;
				runFase = 100;
			}
		}
		break;

	case 100:
		if(timeCount<STOP_TIME){
			timeCount++;
			mTracer->stop();
		}else{
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			lineCount = 0;
			timeCount=0;
			runFase = 101;
		}
		break;

	case 101:
		mStraightRunner->setForward(40);
		mStraightRunner->straightRun();
		if(mile > 10){
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			lineCount = 0;
			timeCount=0;
			runFase = 102;
		}
		break;

	case 102:
		mStraightRunner->setForward(40);
		mStraightRunner->straightRun();
		/*
		if((direction==1 && firstTurn+secondTurn+thirdTurn==1) || (direction==3 && firstTurn+secondTurn+thirdTurn==-1) || 
		(direction==0 && secondTurn==0 && firstTurn+thirdTurn==0) || (direction==2 && secondTurn==0 && firstTurn+thirdTurn==0)){
		if(this->lineCounter(goNum - 1)){
		mile_l= mMileage->mileageL();
		mile_r= mMileage->mileageR();
		mRevolver->reset();
		mStraightRunner->reset();
		lineCount = 0;
		timeCount = 0;
		runFase = 110;
		}
		}else{
		*/
		if(this->lineCounter(goNum)){
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			lineCount = 0;
			timeCount = 0;
			runFase = 104;
		}
		//}
		break;

		/*
		case 110:

		mStraightRunner->setForward(40);
		mStraightRunner->straightRun();
		if(mile>200){
		mile_l= mMileage->mileageL();
		mile_r= mMileage->mileageR();
		mRevolver->reset();
		mStraightRunner->reset();
		lineCount = 0;
		timeCount = 0;
		runFase = 112;
		}

		break;


		case 112:
		timeCount++;
		if(timeCount<STOP_TIME){
		mTracer->stop();
		}else{
		if(mRevolver->revolve(90*thirdTurn)){
		mile_l= mMileage->mileageL();
		mile_r= mMileage->mileageR();
		mRevolver->reset();
		mStraightRunner->reset();
		lineCount = 0;
		timeCount = 0;
		runFase = 114;
		}
		}
		break;

		case 114:
		timeCount++;
		if(timeCount<STOP_TIME){
		mTracer->stop();
		}else{
		mile_l= mMileage->mileageL();
		mile_r= mMileage->mileageR();
		mRevolver->reset();
		mStraightRunner->reset();
		lineCount = 0;
		timeCount = 0;
		runFase = 116;
		}
		break;

		case 116:
		mStraightRunner->setForward(40);
		mStraightRunner->straightRun();
		if(this->lineCounter(1)){
		mile_l= mMileage->mileageL();
		mile_r= mMileage->mileageR();
		mRevolver->reset();
		mStraightRunner->reset();
		lineCount = 0;
		timeCount = 0;
		thirdTurn *= -1;
		runFase = 104;
		}
		break;
		*/

	case 104:
		if(mReturnLine->lineReturn(thirdTurn)){
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			lineCount = 0;
			circleCatchInit = false;
			if(thirdTurn == 1) mTracer->setEdge(LEFT_EDGE);
			else mTracer->setEdge(RIGHT_EDGE);
			runFase = 255;
		}
		break;

	case 200:
		if(this->circleCatch()){
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			lineCount = 0;
			circleCatchInit = false;
			runFase = 255;
		}
		break;


	case 240:
		timeCount++;
		if(timeCount<STOP_TIME) mTracer->stop();
		else{
			if(mLineMonitor->checkBrightness() > 10){

				if(mRevolver->revolve(-40)){
					mile_l= mMileage->mileageL();
					mile_r= mMileage->mileageR();
					mRevolver->reset();
					mStraightRunner->reset();
					lineCount = 0;
					timeCount = 0;
					runFase = 242;
				}
			}else{
				mile_l= mMileage->mileageL();
				mile_r= mMileage->mileageR();
				mRevolver->reset();
				mStraightRunner->reset();
				lineCount = 0;
				timeCount = 0;
				mTracer->setEdge(RIGHT_EDGE);
				runFase = 255;
			}
		}
		break;

	case 242:

		if(mLineMonitor->checkBrightness() > 10){
			if(mRevolver->revolve(80)){
				mile_l= mMileage->mileageL();
				mile_r= mMileage->mileageR();
				mRevolver->reset();
				mStraightRunner->reset();
				lineCount = 0;
				timeCount = 0;
				runFase = 240;
			}
		}else{
			mile_l= mMileage->mileageL();
			mile_r= mMileage->mileageR();
			mRevolver->reset();
			mStraightRunner->reset();
			lineCount = 0;
			timeCount = 0;
			mTracer->setEdge(LEFT_EDGE);
			mRevolver->setForward(0);
			runFase = 255;
		}

		break;




	case 255:

		patternInit = false;
		mRevolver->setForward(0);
		return true;

		break;
	}

	return false;
}

bool BlockErea::lineCounter(int num){

	bright = mLineMonitor->checkBrightness();

	if(!lineCounterInit){
		lineCount = 0;
		brightBuff = bright;
		lineCounterInit = true;
	}

	if(lineCount == num || lineCount<0){
		lineCount = 0;
		lineCounterInit = false;
		return true;
	}

	if(bright<10){
		timeCount++;
	}else{
		timeCount = 0;
	}

	if(timeCount == 5) lineCount++;

	/*
	if(timeCount == 10){
	if(brightBuff - bright > 40) lineCount++;
	brightBuff = bright;
	timeCount = 0;
	}
	*/
	//timeCount++;

	//mLogger->addData(bright);
	//mLogger->addData(brightBuff);
	//mLogger->addData(lineCount);

	return false;

}


