// Pid.cpp
// author: Tokuta
// Data 2013.06.17

#include "Pid.h"

//****************************************************************************************************
//�R���X�g���N�^
//�֐����FPid
//****************************************************************************************************
Pid::Pid(void)
{
	kp = 0.88;
	ki = 0.001;
	kd = 0.08;
	diff[1] = 0.0;
	//diff_s[1] = 0.0;
	integral = 0.0;
	//integral_s = 0.0;
	//limit = 100;
}

//****************************************************************************************************
//�f�X�g���N�^
//�֐����F~Pid
//****************************************************************************************************
Pid::~Pid(void)
{

}

//****************************************************************************************************
//PID�Q�C���ݒ�
//�֐����FsetGain
//****************************************************************************************************
void Pid::setGain(float pGain, float iGain, float dGain)
{
	kp = pGain;
	ki = iGain;
	kd = dGain;
}

/*void Pid::setGain_s(F32 pGain, F32 iGain, F32 dGain)
{
kp_s = pGain;
ki_s = iGain;
kd_s = dGain;
}*/

void Pid::reset(){
	diff[1] = 0.0;
	integral = 0.0;
}

void Pid::getGain(float pGain, float iGain, float dGain){
	pGain = kp;
	iGain = ki;
	dGain = kd;
}

//****************************************************************************************************
//PID����
//�֐����FpidControl
//****************************************************************************************************
float Pid::pidControl(float sensorVal, float targetVal)
{
	//Calculator calc;

	static const float DELTA_T = 0.002;
	float p, i, d;
	float ctrlVal;		// ������

	diff[0] = diff[1];					// �O���̕΍�������
	diff[1] = sensorVal - targetVal;		// �����̕΍����擾
	integral += (diff[1] + diff[0]) / 2.0 * DELTA_T;

	// ���ፀ�E�ϕ����E�󕪍�
	p = kp * diff[1];
	i = ki * integral;
	d = kd * (diff[1] - diff[0]) / DELTA_T;	

	// ������
	ctrlVal = p + i + d;

	//if(ctrlVal > limit) ctrlVal = limit;
	//else if(ctrlVal < -80) ctrlVal = -limit;

	return ctrlVal;
}

/*F32 Pid::pidControl_s(F32 sensorVal, F32 targetVal)
{
//Calculator calc;

static const F32 DELTA_T = 0.004;
F32 p, i, d;
F32 ctrlVal;		// ������

diff_s[0] = diff_s[1];					// �O���̕΍�������
diff_s[1] = sensorVal - targetVal;		// �����̕΍����擾
integral_s += (diff_s[1] + diff_s[0]) / 2.0 * DELTA_T;

// ���ፀ�E�ϕ����E�󕪍�
p = kp * diff_s[1];
i = ki * integral;
d = kd * (diff_s[1] - diff_s[0]) / DELTA_T;	

// ������
ctrlVal = p + i + d;

//if(ctrlVal > limit) ctrlVal = limit;
//else if(ctrlVal < -80) ctrlVal = -limit;

return ctrlVal;
}*/
