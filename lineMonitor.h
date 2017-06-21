#ifndef EV3_UNIT_LINEMONITOR_H_
#define EV3_UNIT_LINEMONITOR_H_

#include "ev3api.h"
#include "ColorSensor.h"
#include "Sensor.h"
#include "Logger.h"

class LineMonitor {
    public:
        LineMonitor(ev3api::ColorSensor* colorSensor, Logger* logger);
        ~LineMonitor();
        int8_t checkBrightness();
       
    
    private:
        ev3api::ColorSensor* mColorSensor;
		Logger *mLogger;
		int8_t brightness;

};

#endif