#ifndef EV3_UNIT_BASICCOURSER_H_
#define EV3_UNIT_BASICCOURSER_H_

#include "ev3api.h"
#include "tracer.h"
#include "mileage.h"
#include "changeEdge.h"
#include "straightRunner.h"
#include "Logger.h"

class BasicCourseR{
    public:
        BasicCourseR(
            Mileage* mileage,
            Tracer* tracer,
            ChangeEdge* changeEdge,
            StraightRunner* straightRunner,
            Logger* logger
        );
        ~BasicCourseR();

        bool run();
    private:
        Mileage* mMileage;
        Tracer* mTracer;
        ChangeEdge* mChangeEdge;
        StraightRunner* mStraightRunner;
        Logger* mLogger;
        int distance;
        int offset;
        int fase;
        char firstFlag;


};

#endif