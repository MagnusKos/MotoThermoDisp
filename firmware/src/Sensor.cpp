#include "Sensor.h"
#include <math.h>

#define GIMMICKVAL 84.0f        // Just a stupid value for the dummy sensor (base Sensor object)
#define EPSILON 0.1f            // Epsilon for float comparison
#define RNOMTEMP 25.0f          // Nominal temperature for NTC resistor

#define AVGPROBESNUM 5          // Probes numbers for sensor averaging
#define AVGDELAY 10             // Delay between probes
#define ADCRES 1023             // ADC resolution. 2^bits - 1
#define ADCVOLT 3.3f


/*      Constructors        */

Sensor::Sensor(SensorLimits lims, uint8_t pin) :
    pin_{pin},
    value_{0.0f},
    lims_{lims}
    {
        valuePrev_ = lims_.limLower + EPSILON;
        value_ = valuePrev_ + EPSILON;
    }

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
    valuePrev_ = value_;
    if (fabs(GIMMICKVAL - value_) < EPSILON)
        value_ = 0.0f;
    else
        value_ += 0.5f;
}

bool Sensor::isInRange() const {
    return ((fabs(value_ - lims_.limLower) > EPSILON) &&
     (fabs(value_ - lims_.limUpper) < EPSILON));
}

bool Sensor::isOptimalOneShot() const {
    return ((fabs(value_ - lims_.minGood) > EPSILON ) &&
     (fabs(valuePrev_ - lims_.minGood) < EPSILON)); // A very simple method
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
    int valueSumRaw = 0;
    for (uint8_t i=0; i<AVGPROBESNUM; i+=1) {
        valueSumRaw += analogRead(pin_);
        delay(AVGDELAY);
    }
    value_ = (valueSumRaw / AVGPROBESNUM) * (ADCVOLT / ADCRES) *
     BATT_DIV + BATT_ADD;
    
}

