#ifndef EV3_UNIT_TRACER_H_
#define EV3_UNIT_TRACER_H_

#include "ev3api.h"
#include "driver.h"
#include "lineMonitor.h"
#include "Sensor.h"
#include "Pid.h"
#include "colorMonitor.h"

class Tracer {
    public:
        Tracer(Driver* driver, LineMonitor* lineMonitor, Logger* logger, ColorMonitor* colorMonitor);
        ~Tracer();
        void run();
        void stop();
        void setTargetBrightness(int8_t black, int8_t white);
		void setTargetColor(rgb_raw_t _blackColor, rgb_raw_t _whiteColor);
        void setCommand(int8_t _forward, int _curvature);
        void setEdge(char _edge);
		void reset();
		void setMode(int _mode);

		void changeGain(int _cource);

		rgb_raw_t color;

        int8_t turn;     //旋回量 
    
    private:

		rgb_raw_t colorInit(uint16_t r, uint16_t g, uint16_t b);

        Driver* mDriver;
        LineMonitor* mLineMonitor;
        Pid* pid;
		Logger* mLogger;
		ColorMonitor* mColorMonitor;

        int8_t forward;  //前進量
              
        //int8_t target;
        int8_t black;
        int8_t white;
        float bright;
        int curvature;
        char edge;

		float buff[2];
		bool firstFlag;
		int mode;

		rgb_raw_t blackColor;
		rgb_raw_t whiteColor;

		
		int colorAverage;
		int blackAverage;
		int whiteAverage;

		float kp, ki, kd;
};

#endif
