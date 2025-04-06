#include "timer.h"

TIMER_t* TIMER_Init( TIMER_CONFIG_t cfg )
{
    TIMER_t* timer;

    timer = (TIMER_t*)malloc( sizeof ( TIMER_t ) );
    
    assert( timer != NULL );

    if( cfg.type == TIMER_PERIODIC )
    {
        add_repeating_timer_ms( cfg.timeout , cfg.periodic_callback , NULL, &timer->timer );
    }
    else
    {
        add_alarm_in_ms( cfg.timeout , cfg.alarm_callback , NULL, false );
    }
    return timer;
}
