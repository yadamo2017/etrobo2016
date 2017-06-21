#include "status.h"

Status::Status(){
	orientation = 0;
	x = 0;
	y = 0;
}

Status::~Status(){}

void Status::setStatus(int _orientation, int _x, int _y){
	orientation = _orientation;
	x = _x;
	y = _y;
}