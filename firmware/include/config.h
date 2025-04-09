#pragma once


/* * * * * * * * * * * * * * * * * * * * * * * * * * *
    Section: basic parameters
    Edit these parameters first to fulfil your setup. 
* * * * * * * * * * * * * * * * * * * * * * * * * * */


/* * * * *
 Warnings to show. Comment out any if you don't need them
* * * * */
#define WARN_EN_GREET
//#define WARN_EN_OVERHEAT
//#define WARN_EN_RTG
//#define WARN_EN_BADVOLT


/* * * * *
 Displayed messages. Do not delete quotes!
* * * * */
#define MSG_GREET "M1NSK"       // Greet/startup message


/* * * * *
 Thermal sensing parameters.
 Connect NTC and Rdiv like this:
 (Vcc)---[Rdiv]---(pin)---[NTC]---(GND)
* * * * */
#define SENSOR_ENGINE_BETA 3900.0f
#define SENSOR_ENGINE_R25 50000.0f    // Nominal resistance at 25 Celicus, in Ohms
#define SENSOR_ENGINE_RDIV 10000.0f   // Divider resistor's value Ohms

#define SENSOR_AIR_BETA 3900.0f
#define SENSOR_AIR_R25 2200.0f     // Nominal resistance at 25 Celicus, in Ohms
#define SENSOR_AIR_RDIV 10000.0f   // Divider resistor's value Ohms

/*
 Engine temperatures: Ready-to-Go (RTG), OverHeated (OH) and TooCold (TC)
*/
#define ENGINE_RTG 75.0f         // In Celcius
#define ENGINE_OH 110.0f         // In Celcius
#define ENGINE_TC -15.0f         // In Celcius

/*
 Air temperatures: Comfy (OK), OverHeated (OH) and TooCold (TC)
*/
#define AIR_OK 25.0f             // In Celcius
#define AIR_OH 50.0f             // In Celcius
#define AIR_TC -15.0f            // In Celcius


/* * * * *
 Battery voltages: UnderVoltage (UV), OverVoltage (OV), normal (OK),
 compensation term (i.e. diode drop voltage), divisioner.
 Connect divider's resistors like this:
 (Vext)---[Rbig]---(pin)---[Rsmall]---(GND)
* * * * */
#define BATT_UV 11.0f            // In Volts
#define BATT_OV 15.0f            // In Volts
#define BATT_OK 12.0f            // In Volts
#define BATT_ADD 0.0f            // In Volts
#define BATT_DIV 5.55f           // Vbatmax / Vadcmax = DIV; 16V / 3.3V = 4.84; 4.85 is good for 100k/27k divider
/*
    Batt_divs suggested values and resistors:
    16/3.3 = 4.84:
        100k/22k = 5.55 -> 2.88V on ADC at 16Vin
        100k/27k = 4.70 -> 3.4V on ADC at 16Vin
        100k/33k = 4.03 -> 3.97V on ADC at 16Vin
    16/5 = 3.2:
        120k/47k = 3.55 -> 4.51V on ADC at 16Vin
        100k/47k = 3.13 -> 5.11V on ADC at 16Vin
*/


/* * * * *
 Connected i2c display's address, type, main font, width, height
* * * * */
#define DISP_I2C_ADDR 0x3C
#define DISP_TYPE U8X8_SH1106_128X32_VISIONOX_HW_I2C
#define DISP_FONT u8x8_font_amstrad_cpc_extended_r
#define DISP_W 128
#define DISP_H 32
