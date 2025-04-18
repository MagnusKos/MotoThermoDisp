#include <Arduino.h>

#include "pins.h"
#include "config.h"
#include "Sensor.h"
#include "DataConnector.h"
#include "DisplayManager.h"
#include "FiniteStateMachine.h"

DataConnector *dc;

Sensor *sensAir;
Sensor *sensEngine;
Sensor *sensBatt;

Button2 *butLeft;
Button2 *butRight;

DisplayManager *dm;
DISP_TYPE *u8x8Disp;


void setup() {
  u8x8Disp = new DISP_TYPE(U8X8_PIN_NONE, I2C_SDC_PIN, I2C_SDA_PIN);
  u8x8Disp->begin();

  sensAir = new SensorTemperature(
    SensorLimits{AIR_TC, AIR_OH, AIR_OK}, ADC_AIR_PIN,
    NTCParams {SENSOR_AIR_BETA, SENSOR_AIR_R25, SENSOR_AIR_RDIV});
  sensEngine = new SensorTemperature(
    SensorLimits{ENGINE_TC, ENGINE_OH, ENGINE_RTG}, ADC_ENGINE_PIN,
    NTCParams {SENSOR_ENGINE_BETA, SENSOR_ENGINE_R25, SENSOR_ENGINE_RDIV});
  sensBatt = new SensorVoltage(
    SensorLimits{BATT_UV, BATT_OV, BATT_OK}, ADC_BATT_PIN,
    PowerParams {BATT_ADD, BATT_DIV}); 

  butLeft = new Button2(BUT_LEFT_PIN, INPUT);
  butRight = new Button2(BUT_RIGHT_PIN, INPUT);

  dc = new DataConnector(sensEngine, sensAir, sensBatt);
  dm = new DisplayManager(u8x8Disp, dc);

  FiniteStateMachine::initFSM(sensAir, sensEngine, sensBatt, butLeft, butRight, dm);
}


void loop() {
  FiniteStateMachine::runFSM();
}
