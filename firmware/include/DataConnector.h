#pragma once

#include "Sensor.h"
#include "Frame.h"

class DataConnector {
    public:
        DataConnector(Sensor *e, Sensor *a, Sensor *b);
        void reconnect(Frame const *frame, float const *valuePtr);
    private:
        Sensor *sensEngine_;
        Sensor *sensAir_;
        Sensor *sensBattery_;
};