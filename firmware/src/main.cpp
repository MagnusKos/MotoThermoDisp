#include <Arduino.h>

#include "pins.h"
#include "config.h"
#include "Sensor.h"
#include "DataConnector.h"
#include "DisplayManager.h"
#include "FiniteStateMachine.h"

DataConnector *dc;

Sensor *airSens;
Sensor *engineSens;
Sensor *battSens;

Button2 *butLeft;
Button2 *butRight;

DisplayManager *dm;
DISP_TYPE *u8x8Disp;


void setup() {

  u8x8Disp = new DISP_TYPE(U8X8_PIN_NONE, I2C_SDC_PIN, I2C_SDA_PIN);
  u8x8Disp->begin();

  airSens = new Sensor(
    SensorLimits{-10.0f, 100.0f, 75.0f}, ADC_AIR_PIN);
  engineSens = new Sensor(
    SensorLimits{-10.0f, 100.0f, 75.0f}, ADC_ENGINE_PIN);
  battSens = new Sensor(
    SensorLimits{-10.0f, 100.0f, 75.0f}, ADC_BATT_PIN);

  butLeft = new Button2(BUT_LEFT_PIN, INPUT);
  butRight = new Button2(BUT_RIGHT_PIN, INPUT);

  dc = new DataConnector(engineSens, airSens, battSens);
  dm = new DisplayManager(u8x8Disp, dc);

  FiniteStateMachine::initFSM(airSens, engineSens, battSens, butLeft, butRight, dm);
}


void loop() {
  FiniteStateMachine::runFSM();
}
