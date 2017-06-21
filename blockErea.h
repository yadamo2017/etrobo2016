#ifndef EV3_UNIT_BLOCKEREA_H_
#define EV3_UNIT_BLOCKEREA_H_

#include "ev3api.h"
#include "straightRunner.h"
#include "mileage.h"
#include "revolver.h"
#include "tracer.h"
#include "colorMonitor.h"
#include "armControler.h"
#include "lineMonitor.h"
#include "returnLine.h"
#include "status.h"
#include "Logger.h"

typedef struct {
	int x;
	int y;
	char color;
	bool flag;
} Map;

class BlockErea{
public:
	BlockErea(
		StraightRunner* straightRunner,
		Mileage* mileage,
		Revolver* revolver,
		Tracer* tracer,
		ArmControler* armControler,
		ColorMonitor* colorMonitor,
		LineMonitor* lineMonitor,
		ReturnLine* returnLine,
		Logger* logger
		);
	~BlockErea();

	bool run();

	bool circleCatch();
	bool blockCatch();
	bool blockJudge();

private:
	StraightRunner* mStraightRunner;
	Mileage* mMileage;
	Revolver* mRevolver;
	Tracer* mTracer;
	ArmControler* mArmControler;
	ColorMonitor* mColorMonitor;
	LineMonitor* mLineMonitor;
	ReturnLine* mReturnLine;
	Logger* mLogger;

	char fase;
	

	Map superBlock;
	Map block[3];
	Map gool;
	bool isFirstFlag;
	bool circleCatchInit;
	bool blockCatchInit;
	bool blockJudgeInit;
	bool lineCounter(int num);
	
	Map nextPlace(Status* status);
	Map calcSetPlace(int blockColor, Status* status);
	bool patternRun(Status* status, Map gool);


	double mile_r,mile_l;
	int lineCount;
	int timeCount;
	int bright;
	int brightBuff;

	rgb_raw_t color;

	int angle;

	double mile;

	int bjFase;
	int ccFase;
	int bcFase;
	int colorCount;
	Status* status;

	int turn;

	int firstTurn;
	int secondTurn;
	int thirdTurn;
	int direction;
	int goNum;

	int runFase;

	bool patternInit;
	bool lineCounterInit;

	int carryBlock;
	int loopCount;

	int endLineCountX;
	int endLineCountY;

	int blackCount;
};

#endif