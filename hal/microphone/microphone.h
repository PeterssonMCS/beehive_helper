#ifndef _HAL_MICROPHONE_H
#define _HAL_MICROPHONE_H

#include "../hardware/adc/adc.h"
#include "../hardware/gpio/gpio.h"

#define BUFFER_SIZE 1000

typedef struct
{
    ADC_t* adc;
    uint16_t adc_buffer[BUFFER_SIZE];
}MICROPHONE_t;

typedef struct
{
    ADC_CONFIG_t adc_cfg;
}MICROPHONE_CONFIG_t;

MICROPHONE_t* MICROPHONE_Init( MICROPHONE_CONFIG_t );

void MICROPHONE_Update( MICROPHONE_t* );

void MICROPHONE_Show( MICROPHONE_t* );

#endif