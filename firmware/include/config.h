#pragma once


/* 
    Section: basic parameters
    Edit these parameters first to fulfil your setup. 
*/

// Time between updates of the sensors' data, in seconds
#define DATA_UPDATE_PERIOD 2

// Thermal sensing parameters
#define SENSOR_ENGINE_BETA 3000
#define SENSOR_ENGINE_R25 50    // Nominal resistance at 25 Celicus, in kOhms
#define SENSOR_ENGINE_RDIV 10   // Divider resistor's value kOhms

#define SENSOR_AIR_BETA 3000
#define SENSOR_AIR_R25 10       // Nominal resistance at 25 Celicus, in kOhms
#define SENSOR_AIR_RDIV 10      // Divider resistor's value kOhms

// Engine temperatures: Ready-to-Go (RTG) and OverHeated (OH)
#define ENGINE_RTG 75           // In Celcius
#define ENGINE_OH 110           // In Celcius

// Battery voltages: UnderVoltage (UV), OverVoltage (OV), compensation term (i.e. diode drop voltage), divisioner
#define BATT_UV 11.0
#define BATT_OV 15.0
#define BATT_ADD 0.0
#define BATT_DIV 4.84            // Vbatmax / Vadcmax = DIV; 16V / 3.3V = 3.2

// Connected i2c display's address, type, main font, width, height
#define DISP_I2C_ADDR 0x3C
#define DISP_TYPE U8X8_SH1106_128X32_VISIONOX_HW_I2C
#define DISP_FONT u8x8_font_amstrad_cpc_extended_r
#define DISP_W 128
#define DISP_H 32
