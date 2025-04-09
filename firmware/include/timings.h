#pragma once

/* 
    Section: timings
    These parameters represents time intervals and periods expressed in milliseconds. 
*/

// Delays before transitions in FSM
#define TIM_TRANS_GRT2IDL 3000      // Greeting to Idle
#define TIM_TRANS_IDL2SNS 1000      // Idle to Sensor_Polling
#define TIM_TRANS_RTG2IDL 5000      // Ready-to-Go to Idle
#define TIM_TRANS_WRN2IDL 5000      // Warning to Idle