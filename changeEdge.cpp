/*
エッジ切り替えを行うクラス
*/

#include "changeEdge.h"

ChangeEdge::ChangeEdge(
	Driver* driver
	){
		mDriver = driver;
}

ChangeEdge::~ChangeEdge(){}

void ChangeEdge::edgeChange(char edge, int forward){
	if(edge == 0){
		mDriver->setCommand(forward, 10);
	}else{
		mDriver->setCommand(forward, -10);
	}
}