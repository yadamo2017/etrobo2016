#ifndef EV3_UNIT_BASICCOURSE_H_
#define EV3_UNIT_BASICCOURSE_H_

#include "ev3api.h"
#include "tracer.h"
#include "mileage.h"
#include "changeEdge.h"

class BasicCourse{
    public:
        BasicCourse(
            Mileage* mileage,
            Tracer* tracer,
            ChangeEdge* changeEdge
        );
        ~BasicCourse();

        void run();
    private:
        Mileage* mMileage;
        Tracer* mTracer;
        ChangeEdge* mChangeEdge;
        int distance;
        int offset;
        char firstFlag;


};

#endif