#include "spi.h"

static void on_spi_rx() 
{
    /*
    while(spi_is_readable(spi0)) 
    {
        uint8_t received = spi_get_hw(spi0)->dr;
        if ( rx_index < BUFFER_SIZE ) 
        {
            rx_buffer[rx_index++] = received;
        }
    }
    */
}

SPI_t* SPI_Init( SPI_CONFIG_t cfg )
{
    SPI_t* spi;

    spi = (SPI_t*)malloc( sizeof ( SPI_t ) );
    
    assert( spi != NULL );

    spi->spi_hw = spi0;
    spi->pin_cs = cfg.pin_cs;

    spi_init( spi->spi_hw , cfg.frequency );
    gpio_set_function( cfg.pin_clk , GPIO_FUNC_SPI );
    gpio_set_function( cfg.pin_mosi , GPIO_FUNC_SPI );
    gpio_set_function( cfg.pin_miso , GPIO_FUNC_SPI );
    gpio_set_function( cfg.pin_cs , GPIO_FUNC_SPI );

    irq_set_exclusive_handler( SPI0_IRQ , on_spi_rx );
    irq_set_enabled( SPI0_IRQ , true );
    //spi_get_hw( spi->spi_hw )->imsc = SPI_IMSC_RXIM_BITS;

    return spi;
}

size_t SPI_WriteByte( SPI_t* spi , const uint8_t* buffer )
{
    size_t success;
    gpio_put( spi->pin_cs , 0 );
    success = spi_write_blocking( spi->spi_hw , buffer , 1 );
    gpio_put( spi->pin_cs , 1 );
    if( success == 1 ) { return true; } else { return false; }
}

size_t SPI_WriteByteArray( SPI_t* spi , const uint8_t* buffer , size_t length )
{
    size_t success;
    gpio_put( spi->pin_cs , 0 );
    success = spi_write_blocking( spi->spi_hw , buffer , length );
    gpio_put( spi->pin_cs , 1 );
    if( success == length ) { return true; } else { return false; }
}