#ifndef EV3_UNIT_COLORMONITOR_H_
#define EV3_UNIT_COLORMONITOR_H_

#include "ev3api.h"
#include "ColorSensor.h"
#include "Sensor.h"
#include "Logger.h"

class ColorMonitor {
    public:
        ColorMonitor(ev3api::ColorSensor* colorSensor, Logger* logger);
        ~ColorMonitor();
        void checkColor(rgb_raw_t& rgb);
		int colorJudge(rgb_raw_t& rgb, char arm);
		int colorJudge2(rgb_raw_t& rgb, char arm);
        
    
    private:
        ev3api::ColorSensor* mColorSensor;
		rgb_raw_t color[4];
		rgb_raw_t blockColor[5];
		Logger* mLogger;
};

#endif