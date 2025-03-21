#pragma once

#include <Arduino.h>
#include <Thermistor.h>
#include <NTC_Thermistor.h>
#include <AverageThermistor.h>

#include "config.h"
#include "pins.h"

enum SensorId {         // Do we need this?
    ENGINE_SENSOR,
    AIR_SENSOR,
    BATTERY_SENSOR
};

struct SensorLimits {
    float limLower;
    float limUpper;
    float minGood;
};

struct NTCParams {
    float beta;
    float r25;
    float rDiv;
};

struct PowerParams {
    float vAdd;
    float vDiv;
};

class Sensor {
    public:
        Sensor(SensorLimits lims, uint8_t pin);
        virtual void update();

        bool isInRange() const;                 // Checks value is in a predefined range
        bool isOptimalOneShot() const;          // Checks value reached a zone of optimality
        float getValue() const;
        float const* getValuePtr() const;       // Can provoke UB if the object destroyed, cause somewhere the pointer exists

    protected:
        //uint8_t id_;                          // Do we need this?
        uint8_t const pin_;
        float value_;
        float valuePrev_;
        SensorLimits const lims_;

};


class SensorVoltage : public Sensor {
    public:
        SensorVoltage(SensorLimits lims, uint8_t pin, PowerParams pp);
        void update() override;
    private:
        PowerParams const pp_;
};


class SensorTemperature : public Sensor {
    public:
        SensorTemperature(SensorLimits lims, uint8_t pin, NTCParams np);
        void update() override;
    private:
        NTCParams const np_;
        NTC_Thermistor thermo_;
        AverageThermistor thermoAvg_;
};