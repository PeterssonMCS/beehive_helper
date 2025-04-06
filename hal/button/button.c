#include "button.h"

BUTTON_t* BUTTON_Init( BUTTON_CONFIG_t cfg )
{
    BUTTON_t* button;

    button = (BUTTON_t*)malloc( sizeof ( BUTTON_t ) );
    
    assert( button != NULL );

    button->gpio = GPIO_Init( cfg.gpio_cfg );
    BUTTON_Update( button );

    return button;
}

void BUTTON_Update( BUTTON_t* button )
{
    button->state = GPIO_GetInput( button->gpio );
}

bool BUTTON_GetState( BUTTON_t* button )
{
    return button->state;
}