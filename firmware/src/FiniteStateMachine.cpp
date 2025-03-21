#include "FiniteStateMachine.h"

namespace FiniteStateMachine {

// Hidden variables' definitions
    namespace detail {
        State states_[] = {
            State("greeting", onGreet),                // Welcoming message
            State("idle", onIdle),                     // Idle state, waits
            State("frame_l_change", onFrameLeft),     // Changes left frame configuration
            State("frame_r_change", onFrameRight),    // Changes right frame configuration
            State("sensor_poll", onSensorPoll),       // Polls adcs and gets sensors' data
            State("issue_overheat", onOverheat),       // Shows overheat message
            State("issue_voltage", onVoltageBad),     // Shows bad voltage message
            State("ready_to_go", onRtg)                // Shows ready-to-go message
        };

        Transition trigTransitions_[] = {
            Transition(&states_[1], &states_[2], TRIG_BUTTON_LEFT),
            Transition(&states_[1], &states_[3], TRIG_BUTTON_RIGHT),
            Transition(&states_[2], &states_[1], TRIG_RETURN),
            Transition(&states_[3], &states_[1], TRIG_RETURN),
            Transition(&states_[4], &states_[1], TRIG_RETURN),
            Transition(&states_[4], &states_[5], TRIG_OVERHEAT),
            Transition(&states_[4], &states_[6], TRIG_BAD_VOLT),
            Transition(&states_[4], &states_[7], TRIG_RTG),
            Transition(&states_[5], &states_[1], TRIG_BUTTON_LEFT),
            Transition(&states_[5], &states_[1], TRIG_BUTTON_RIGHT),
            Transition(&states_[6], &states_[1], TRIG_BUTTON_LEFT),
            Transition(&states_[6], &states_[1], TRIG_BUTTON_RIGHT)
        };

        TimedTransition timedTransitions_[] = {
            TimedTransition(&states_[0], &states_[1], TIM_TRANS_GRT2IDL),
            TimedTransition(&states_[1], &states_[4], TIM_TRANS_IDL2SNS),
            TimedTransition(&states_[5], &states_[1], TIM_TRANS_RTG2IDL),
            TimedTransition(&states_[6], &states_[1], TIM_TRANS_WRN2IDL),
            TimedTransition(&states_[7], &states_[1], TIM_TRANS_WRN2IDL)
        };

// Hidden functions

        void handlerButLeft(Button2 &btn) {
            fsmBack_.trigger(TRIG_BUTTON_LEFT);
        }

        void handlerButRight(Button2 &btn) {
            fsmBack_.trigger(TRIG_BUTTON_RIGHT);
        }

        // States' functions

        void onGreet() {
            #ifdef WARN_EN_GREET
                dm_->showWarning(GREETING);
            #endif
        }

        void onIdle() {
            dm_->draw();
        }

        void onFrameLeft() {
            dm_->switchLFrame();
            fsmBack_.trigger(TRIG_RETURN);
        }

        void onFrameRight() {
            dm_->switchRFrame();
            fsmBack_.trigger(TRIG_RETURN);
        }

        void onSensorPoll() {
            engineSens_->update();
            battSens_->update();
            airSens_->update();
            #ifdef WARN_EN_OVERHEAT
                if (!(engineSens_->isInRange())) {
                    fsmBack_.trigger(TRIG_OVERHEAT); // Overheating is more demanding, so ignore voltage problems
                }
                else 
            #endif
            #ifdef WARN_EN_BADVOLT
                if (!(battSens_->isInRange())) {
                    fsmBack_.trigger(TRIG_BAD_VOLT);
                }
                else
            #endif
            #ifdef WARN_EN_RTG
                if (engineSens_->isOptimalOneShot()) {
                    fsmBack_.trigger(TRIG_RTG);
                }
                else
            #endif
                    fsmBack_.trigger(TRIG_RETURN);    // Just return to the idle state if everything is ok
        }

        void onOverheat() {
            #ifdef WARN_EN_OVERHEAT
                dm_->showWarning(OVERHEAT);
            #endif
        }

        void onVoltageBad() {
            #ifdef WARN_EN_BADVOLT
                dm_->showWarning(BATT_PROBLEM);
            #endif
        }

        void onRtg() {
            #ifdef WARN_EN_RTG
                dm_->showWarning(TRIG_RTG);
            #endif
        }
    }   // End of namespace detail

// Client's functions

void initFSM(Sensor *a, Sensor *e, Sensor *b, Button2 *bl, Button2 *br, DisplayManager *dm) {
        using namespace detail;
        airSens_ = a;
        engineSens_ = e; 
        battSens_ = b;
        butLeft_ = bl;
        butRight_ = br;
        dm_ = dm; 

        fsmBack_.add(trigTransitions_, NUM_STATE_TRANS_TRG);
        fsmBack_.add(timedTransitions_, NUM_STATE_TRANS_TIM);
        fsmBack_.setInitialState(&states_[0]);

        butLeft_->setTapHandler(handlerButLeft);
        butRight_->setTapHandler(handlerButRight);

        isInit = true;
    }

void runFSM() {
        detail::fsmBack_.run();
        detail::butLeft_->loop();
        detail::butRight_->loop();
    }

}