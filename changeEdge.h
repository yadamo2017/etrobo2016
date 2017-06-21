#ifndef EV3_UNIT_CHANGEEDGE_H_
#define EV3_UNIT_CHANGEEDGE_H_

#include "ev3api.h"
#include "driver.h"

class ChangeEdge {
    public:
        ChangeEdge(
            Driver* driver
        );
        ~ChangeEdge();

        void edgeChange(char edge, int forward);

    private:
        Driver* mDriver;
};

#endif