#ifndef EV3_UNIT_ARMCONTROLER_H_
#define EV3_UNIT_ARMCONTROLER_H_


#include "ev3api.h"
#include "Motor.h"
#include "Sensor.h"

class ArmControler {
    public:
        ArmControler(
            ev3api::Motor* armMotor
        );
        ~ArmControler();
        void armControl(int32_t deg);
		void setForward(int _pwm);
		float pwm;
		int forward;

    private:
            ev3api::Motor* mArmMotor;
            
};

#endif

