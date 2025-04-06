#ifndef _HAL_SPI_H
#define _HAL_SPI_H

#include <stdint.h>
#include "pico/stdlib.h"
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <hardware/spi.h>
#include <hardware/irq.h>

typedef struct
{
    spi_inst_t* spi_hw;
    uint8_t pin_cs;
}SPI_t;

typedef struct
{
    uint32_t frequency;
    uint8_t pin_mosi;
    uint8_t pin_miso;
    uint8_t pin_clk;
    uint8_t pin_cs;
}SPI_CONFIG_t;

SPI_t* SPI_Init( SPI_CONFIG_t );

size_t SPI_WriteByte( SPI_t* , const uint8_t* );

size_t SPI_WriteByteArray( SPI_t* , const uint8_t* , size_t );

#endif