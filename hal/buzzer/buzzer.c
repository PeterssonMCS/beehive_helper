#include "buzzer.h"

BUZZER_t* BUZZER_Init( BUZZER_CONFIG_t cfg )
{
    BUZZER_t* buzzer;

    buzzer = (BUZZER_t*)malloc( sizeof ( BUZZER_t ) );
    
    assert( buzzer != NULL );

    buzzer->pwm = PWM_Init( cfg.pwm_cfg );
    BUZZER_Disable( buzzer );
    return buzzer;
}

size_t BUZZER_SetVolume( BUZZER_t* buzzer , float volume )
{
    assert( volume >= 0 && volume <= 1.0 );
    PWM_SetDuty( buzzer->pwm , volume );
}

size_t BUZZER_SetFrequency( BUZZER_t* buzzer , float frequency )
{

}

void BUZZER_Enable( BUZZER_t* buzzer )
{
    PWM_Enable( buzzer->pwm );
}

void BUZZER_Disable( BUZZER_t* buzzer )
{
    PWM_Disable( buzzer->pwm );
}