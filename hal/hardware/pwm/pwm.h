#ifndef _HAL_PWM_H
#define _HAL_PWM_H

#include <stdint.h>
#include "pico/stdlib.h"
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <hardware/pwm.h>

typedef struct
{
  uint8_t pin;
  uint8_t pwm_slice;
  uint16_t period;
}PWM_t;

typedef struct
{
    uint8_t pin;
    uint16_t period;
    float divider;
    uint16_t step;
    uint16_t duty;
}PWM_CONFIG_t;

PWM_t* PWM_Init( PWM_CONFIG_t );

void PWM_SetDuty( PWM_t* , float );

void PWM_Enable( PWM_t* );

void PWM_Disable( PWM_t* );

#endif