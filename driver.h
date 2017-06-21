#ifndef EV3_UNIT_DRIVER_H_
#define EV3_UNIT_DRIVER_H_

#include "ev3api.h"
#include "Motor.h"
#include "Sensor.h"
#include "Logger.h"

class Driver {
    public:
        Driver(
            ev3api::Motor* rightMotor,
            ev3api::Motor* leftMotor,
            Logger* logger
        );
        ~Driver();
        void setCommand(int forward, int turn);
        void rotateR(int pwmR);
        void rotateL(int pwmL);


    private:
        ev3api::Motor* mRightMotor;
        ev3api::Motor* mLeftMotor;
        Logger* mLogger;  

        int32_t motorEncR, motorEncL;
        int32_t buffR, buffL;

		int forward;
};

#endif
