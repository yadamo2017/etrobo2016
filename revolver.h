#ifndef EV3_UNIT_REVOLVER_H_
#define EV3_UNIT_REVOLVER_H_

#include "ev3api.h"
#include "driver.h"
#include "mileage.h"
#include "Pid.h"

class Revolver{
    public:
        Revolver(
            Driver* driver,
            Mileage* mileage
        );
        ~Revolver();

        bool revolve(double angle);
        void setForward(int _forward);
        void reset();
		bool toRevolve(int orientation);
    private:
        Driver* mDriver;
        Mileage* mMileage;
        int forward;
        double mile_l, mile_r;
        double ang_l, ang_r;
        bool firstFlag;
		bool secondFlag;
		Pid *pid;
		int pwm_l, pwm_r;

		int buff_orientation;
};

#endif