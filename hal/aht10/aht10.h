#ifndef _HAL_AHT10_H
#define _HAL_AHT10_H

#include "../hardware/i2c/i2c.h"
#include <stdint.h>

#define AHT10_INITIALIZATION 0xE1
#define AHT10_MEASUREMENT 0xAC
#define AHT10_SOFT_RESET 0xBA

typedef struct
{
    I2C_t* i2c;
    uint8_t temperature;
    uint8_t humidity;
    bool is_valid;
}AHT10_t;

typedef struct
{
    I2C_CONFIG_t i2c_cfg;
}AHT10_CONFIG_t;

AHT10_t* AHT10_Init( AHT10_CONFIG_t );

size_t AHT10_Update( AHT10_t* );

void AHT10_TriggerMeasurement( AHT10_t* );

size_t AHT10_ReadStatus( AHT10_t* );

uint8_t AHT10_GetTemperature( AHT10_t* );

uint8_t AHT10_GetHumidity( AHT10_t* );

#endif