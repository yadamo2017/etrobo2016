#pragma once

#include "stdio.h"
#include "ev3api.h"

class Logger{
public:
	Logger();
	bool send();
	void addData(double data);
private:
	double buff[9];
	int ptr;
	char sendData[1024];
	FILE *bt;
};
