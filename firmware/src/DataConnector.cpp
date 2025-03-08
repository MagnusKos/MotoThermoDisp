#include "DataConnector.h"

DataConnector::DataConnector(Sensor *e, Sensor *a, Sensor *b):
    sensEngine_{e}, sensAir_{a}, sensBattery_{b}
    {}

void DataConnector::reconnect(Frame const *frame, float const * &valuePtr)
{
    uint8_t frameContId = frame->getContentId();
    switch (frameContId) {
        case ENGINE:
            valuePtr = sensEngine_->getValuePtr();
            break;
        case AIR:
            valuePtr = sensAir_->getValuePtr();
            break;
        case BATTERY:
            valuePtr = sensBattery_->getValuePtr();
            break;
        default:
            valuePtr = nullptr;
            break;
    }
}