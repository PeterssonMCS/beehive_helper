#include "led.h"

LED_t* LED_Init( LED_CONFIG_t cfg )
{
    LED_t* led;

    led = (LED_t*)malloc( sizeof ( LED_t ) );
    
    assert( led != NULL );

    led->red = PWM_Init( cfg.red );
    led->green = PWM_Init( cfg.green );
    led->blue = PWM_Init( cfg.blue );

    return led;
}

size_t LED_SetColor( LED_t* led , float red , float green , float blue )
{
    assert( red >= 0 && red <= 1.0);
    assert( green >= 0 && green <= 1.0);
    assert( blue >= 0 && blue <= 1.0);
   
    PWM_SetDuty( led->red , red );
    PWM_SetDuty( led->green , green );
    PWM_SetDuty( led->blue , blue );
}
