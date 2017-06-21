#ifndef EV3_UNIT_CALIBRATION_H_
#define EV3_UNIT_CALIBRATION_H_

#include "ev3api.h"
#include "Sensor.h"
#include "lineMonitor.h"
#include "colorMonitor.h"
#include "TouchSensor.h"
#include "Clock.h"

class Calibration {
    public:
        Calibration(
            ev3api::TouchSensor* touchSensor,
            LineMonitor* lineMonitor,
            ColorMonitor* colorMonitor
        );
        ~Calibration();
        void calibrate(rgb_raw_t* rgb_B, int8_t& black, int8_t& white);

    private:
        ev3api::TouchSensor* mTouchSensor;
        LineMonitor* mLineMonitor;
        ColorMonitor* mColorMonitor;
        ev3api::Clock* clock;
};

#endif
