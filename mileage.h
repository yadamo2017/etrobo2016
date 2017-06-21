#ifndef EV3_UNIT_MILEAGE_H_
#define EV3_UNIT_MILEAGE_H_

#include "ev3api.h"
#include "Motor.h"

class Mileage{
    public:
        Mileage(
            ev3api::Motor* rightMotor,
            ev3api::Motor* leftMotor
        );
        ~Mileage();
        double getMileage(); //走行距離取得
        double mileageL(); //左タイヤ走行距離取得
        double mileageR(); //右タイヤ走行距離取得
        void init();
		int orientation();

    private:
        double distanceT, distanceL, distanceR; //走行体の走った距離、右タイヤの走った距離、左タイヤの走った距離[mm]
        int32_t motor_ang_l, motor_ang_r;
        int32_t motorcountL, motorcountR;
        ev3api::Motor* mLeftMotor; 
        ev3api::Motor* mRightMotor;
};

#endif
