#ifndef _HAL_BUTTON_H
#define _HAL_BUTTON_H

#include "../hardware/gpio/gpio.h"

typedef struct
{
    GPIO_t* gpio;
    bool state;
}BUTTON_t;

typedef struct
{
    GPIO_CONFIG_t gpio_cfg;
}BUTTON_CONFIG_t;

BUTTON_t* BUTTON_Init( BUTTON_CONFIG_t );

void BUTTON_Update( BUTTON_t* );

bool BUTTON_GetState( BUTTON_t* );

#endif