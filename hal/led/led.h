#ifndef _HAL_LED_H
#define _HAL_LED_H

#include "../hardware/pwm/pwm.h"

typedef struct
{
    PWM_t* red;
    PWM_t* green;
    PWM_t* blue;
}LED_t;

typedef struct
{
    PWM_CONFIG_t red;
    PWM_CONFIG_t green;
    PWM_CONFIG_t blue;
}LED_CONFIG_t;

LED_t* LED_Init( LED_CONFIG_t );

size_t LED_SetColor( LED_t* , float , float , float );

#endif