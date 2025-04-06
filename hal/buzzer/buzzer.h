#ifndef _HAL_BUZZER_H
#define _HAL_BUZZER_H

#include "../hardware/pwm/pwm.h"

typedef struct
{
    PWM_t* pwm;
}BUZZER_t;

typedef struct
{
    PWM_CONFIG_t pwm_cfg;
}BUZZER_CONFIG_t;

BUZZER_t* BUZZER_Init( BUZZER_CONFIG_t );

size_t BUZZER_SetVolume( BUZZER_t* , float );

size_t BUZZER_SetFrequency( BUZZER_t* , float );

void BUZZER_Enable( BUZZER_t* );

void BUZZER_Disable( BUZZER_t* );

#endif