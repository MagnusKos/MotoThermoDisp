#include "Sensor.h"

#define GIMMICKVAL 42.0f        // Just a stupid value for the dummy sensor (base Sensor object)
#define EPSILON 0.5f            // Epsilon for float comparison
#define RNOMTEMP 25.0f          // Nominal temperature for NTC resistor

#define AVGPROBESNUM 5          // Probes numbers for sensor averaging
#define AVGDELAY 10             // Delay between probes


/*      Constructors        */

Sensor::Sensor(SensorLimits lims, uint8_t pin) :
    pin_{pin},
    value_{0.0f},
    lims_{lims}
    {}

SensorVoltage::SensorVoltage(SensorLimits lims, uint8_t pin, PowerParams pp) :
    Sensor{lims, pin},
    pp_{pp}
    {}

SensorTemperature::SensorTemperature(SensorLimits lims, uint8_t pin, NTCParams np) :
    Sensor{lims, pin},
    np_{np},
    thermo_{pin_, np_.rDiv, np_.r25, RNOMTEMP, np_.beta},
    thermoAvg_{&thermo_, AVGPROBESNUM, AVGDELAY} // 5 probes with 10ms inverval
    {}


/*      Base class methods      */

void Sensor::update() {     // Let's just make a simple saw function
    if (GIMMICKVAL - value_ < EPSILON)
        value_ = 0.0f;
    else
        value_ += 0.5f;
}

float Sensor::getValue() const {
    return value_;
}

float const* Sensor::getValuePtr() const {
    return &value_;
}


/*      Derived classes' methods    */

void SensorTemperature::update() {
    value_ = static_cast<float>(thermoAvg_.readCelsius());
}

void SensorVoltage::update() {
    Sensor::update(); // ToDo: voltage calculation

}
