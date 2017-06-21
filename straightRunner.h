#ifndef EV3_UNIT_STRAIGHTRUNNER_H_
#define EV3_UNIT_STRAIGHTRUNNER_H_

#include "ev3api.h"
#include "driver.h"
#include "Sensor.h"
#include "Pid.h"
#include "mileage.h"
#include "Pid.h"

class StraightRunner {
    public:
        StraightRunner(Driver* driver, Mileage* mileage);
        ~StraightRunner();
        void straightRun();
        void setForward(int8_t _forward);
		void reset();
		void stop();
    private:
        Driver* mDriver;
        Mileage* mMileage;
        
        int8_t forward;
        int8_t pwm_r, pwm_l;

		Pid *pid;
        double enc_r, enc_l;
        double buff_r, buff_l;

		bool firstFlag;
        int count;
};

#endif