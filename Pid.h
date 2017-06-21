// Pid.h
// author: Tokuta
// Data 2013.06.17

#ifndef EV3_UNIT_PID_H_
#define EV3_UNIT_PID_H_


//#include "../include.h"
//#include "Calculator.h"
#include <math.h>

//using namespace ecrobot;

/*
extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "balancer.h"
}
*/


class Pid
{
public:
	Pid();
	~Pid();
	void setGain(float pGain, float iGain, float dGain);
	//void setGain_s(F32 pGain, F32 iGain, F32 dGain);
	float pidControl(float sensorVal, float targetVal);
	//F32 pidControl_s(F32 sensorVal, F32 targetVal);
	float integral;
	//F32 integral_s;
	void reset();
	void getGain(float pGain, float iGain, float dGain);

private:
	float kp, ki, kd;
	//F32 kp_s, ki_s, kd_s;
	float diff[2];
	//F32 diff_s[2];
	//F32 limit;
};

#endif
