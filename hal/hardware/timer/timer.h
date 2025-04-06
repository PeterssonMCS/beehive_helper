#ifndef _HAL_TIMER_H
#define _HAL_TIMER_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <hardware/timer.h>
#include <pico/stdlib.h>

typedef enum
{
    TIMER_ALARM,
    TIMER_PERIODIC
}TIMER_TYPE_t;

typedef struct
{
    struct repeating_timer timer;
}TIMER_t;

typedef struct
{
    int type;
    int timeout;
    bool (*periodic_callback)(struct repeating_timer*);
    int64_t(*alarm_callback)( alarm_id_t , void* );
}TIMER_CONFIG_t;

TIMER_t* TIMER_Init( TIMER_CONFIG_t );

#endif