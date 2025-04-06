#include "pwm.h"

PWM_t* PWM_Init( PWM_CONFIG_t cfg )
{
    PWM_t* pwm;

    pwm = (PWM_t*)malloc( sizeof ( PWM_t ) );
    
    assert( pwm != NULL );
    pwm->period = cfg.period;
    pwm->pin = cfg.pin;
    gpio_set_function( pwm->pin , GPIO_FUNC_PWM );
    pwm->pwm_slice = pwm_gpio_to_slice_num( pwm->pin );
    pwm_set_clkdiv( pwm->pwm_slice , cfg.divider );
    pwm_set_wrap( pwm->pwm_slice , cfg.period - 1 );
    pwm_set_gpio_level( pwm->pin , cfg.duty );
    pwm_set_enabled( pwm->pwm_slice , true);

    return pwm;
}

void PWM_SetDuty( PWM_t* pwm , float perc_duty )
{
    uint16_t duty = perc_duty*pwm->period;
    pwm_set_gpio_level( pwm->pin , duty );
}

void PWM_Enable( PWM_t* pwm )
{
    pwm_set_enabled( pwm->pwm_slice , true);
}

void PWM_Disable( PWM_t* pwm )
{
    pwm_set_enabled( pwm->pwm_slice , false);
}