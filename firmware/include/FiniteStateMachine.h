#pragma once

#include <Arduino.h>

#include <SimpleFSM.h>
#include <Button2.h>

#include "pins.h"
#include "timings.h"
#include "DisplayManager.h"
#include "Sensor.h" 


namespace FiniteStateMachine {

  void initFSM(Sensor *a, Sensor *e, Sensor *b, Button2 *bl, Button2 *br, DisplayManager *dm);
  void runFSM();

  namespace detail {
    inline bool isInit = false;
    inline Sensor *airSens_ = nullptr;
    inline Sensor *engineSens_ = nullptr;
    inline Sensor *battSens_ = nullptr;
    inline DisplayManager *dm_ = nullptr;
    inline Button2 *butLeft_ = nullptr;
    inline Button2 *butRight_ = nullptr;

    inline SimpleFSM fsmBack_;

    void handlerButLeft(Button2 &btn);
    void handlerButRight(Button2 &btn);

    void onGreet();
    void onIdle();
    void onFrameLeft();
    void onFrameRight();
    void onSensorPoll();
    void onOverheat();
    void onVoltageBad();
    void onRtg();

    const int NUM_STATES = 8;           // FSM's number of states
    const int NUM_STATE_TRANS_TRG = 12;  // FSM's number of triggered transitions
    const int NUM_STATE_TRANS_TIM = 5;  // FSM's number of timed transitions

    enum triggers {
        TRIG_BUTTON_LEFT = 1,
        TRIG_BUTTON_RIGHT = 2,
        TRIG_ADC_POLLED = 3,
        TRIG_OVERHEAT = 4,
        TRIG_BAD_VOLT = 5,
        TRIG_RTG = 6,
        TRIG_RETURN = 7
    };

    extern State states_[];
    extern Transition trigTransitions_[];
    extern TimedTransition timedTransitions_[];
  }
}