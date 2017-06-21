#ifndef EV3_UNIT_ETZUMO_H_
#define EV3_UNIT_ETZUMO_H_

#include "ev3api.h"
#include "Clock.h"
#include "Sensor.h"
#include "colorMonitor.h"
#include "lineMonitor.h"
#include "driver.h"
#include "mileage.h"
#include "tracer.h"


class Etzumo {
    public:
        Etzumo(
            ColorMonitor* colorMonitor,
            LineMonitor* lineMonitor,
            Driver* driver,
            Mileage* mileage,
            Tracer* tracer
        );
        ~Etzumo();
        void etzumoRun(int color);

    private:
        ColorMonitor* mColorMonitor;
        LineMonitor* mLineMonitor;
        Driver* mDriver;
        Mileage* mMileage;
        Tracer* mTracer;
        ev3api::Clock* mClock;

        int distance;
        int offset;
        char firstFlag;
        uint32_t time;
        char catchBlack;
};

#endif