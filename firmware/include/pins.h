#pragma once


/* * * * * * * * * * * * * * * * * * * * * * * * * * *
    Section: pins setup
    Edit these parameters first to fulfil your setup. 
* * * * * * * * * * * * * * * * * * * * * * * * * * */


/* * * * *
 ADC pins.
 Used for sensors.
* * * * */
#define ADC_ENGINE_PIN PA0
#define ADC_AIR_PIN PA1
#define ADC_BATT_PIN PA2

// #define ADC_ENGINE_PIN 11
// #define ADC_AIR_PIN 10  //PA1 on STM32F103
// #define ADC_BATT_PIN 9  //PA2 on STM32F103


/* * * * *
 Digital pins.
 Used for input/output.
 Mostly self-explanatory
* * * * */
#define I2C_SDA_PIN 15
#define I2C_SDC_PIN 16

#define BUT_LEFT_PIN 32
#define BUT_RIGHT_PIN 22

#define OUT_THERM_BAD_PIN 14
#define OUT_VOLT_BAD_PIN 13
