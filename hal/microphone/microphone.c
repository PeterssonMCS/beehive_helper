#include "microphone.h"

MICROPHONE_t* MICROPHONE_Init( MICROPHONE_CONFIG_t cfg )
{
    MICROPHONE_t* microphone;

    microphone = (MICROPHONE_t*)malloc( sizeof ( MICROPHONE_t ) );
    
    assert( microphone != NULL );

    microphone->adc = ADC_Init( cfg.adc_cfg );
    
    return microphone;
}

void MICROPHONE_Update( MICROPHONE_t* microphone )
{
    static int index = 0;
    microphone->adc_buffer[index] = ADC_ReadValue( microphone->adc );
    index = index < BUFFER_SIZE ? index + 1 : 0;
}

void MICROPHONE_Show( MICROPHONE_t* microphone )
{
    for( int i = 0 ; i < BUFFER_SIZE ; i++ )
    {
        printf("%d,",microphone->adc_buffer[i]);
    }
    printf("\n");
}