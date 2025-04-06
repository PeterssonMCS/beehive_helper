#include "aht10.h"

AHT10_t* AHT10_Init( AHT10_CONFIG_t cfg )
{
    AHT10_t* aht10;

    aht10 = (AHT10_t*)malloc( sizeof ( AHT10_t ) );
    
    assert( aht10 != NULL );

    aht10->i2c = I2C_Init( cfg.i2c_cfg );
    aht10->is_valid = false;

    char buffer[3] = { AHT10_INITIALIZATION , 0x08 , 0x00 };

    I2C_WriteByteArray( aht10->i2c , buffer , 3 );

    sleep_ms(100);

    return aht10;
}

void AHT10_TriggerMeasurement( AHT10_t* aht10 )
{
    char buffer[3] = { AHT10_MEASUREMENT , 0x33 , 0x00 };
    I2C_WriteByteArray( aht10->i2c , buffer , 3 );
}

size_t AHT10_ReadStatus( AHT10_t* aht10 )
{
    uint8_t status;
    I2C_ReadByte( aht10->i2c , &status );
    return ( status&0x80 != 0) ? 1 : 0;
}

size_t AHT10_Update( AHT10_t* aht10 )
{
    aht10->is_valid = true;
    uint8_t data[6];
    I2C_ReadByteArray( aht10->i2c , data , 6 );
    uint32_t raw_humidity = ((data[1] << 16) | (data[2] << 8) | data[3]) >> 4;
    uint32_t raw_temperature = ((data[3] & 0x0F) << 16) | (data[4] << 8) | data[5];
    aht10->humidity = ( raw_humidity * 100.0 ) / 0x00100000;
    aht10->temperature = (( raw_temperature * 200.0) / 0x00100000 ) - 50.0;
}

uint8_t AHT10_GetTemperature( AHT10_t* aht10 )
{
    if( aht10->is_valid )
    {
        return aht10->temperature;
    } 
    else
    {
        return 0;
    }
}

uint8_t AHT10_GetHumidity( AHT10_t* aht10 )
{
    if( aht10->is_valid )
    {
        return aht10->humidity;
    } 
    else
    {
        return 0;
    }
}

size_t AHT10_USoftReset( AHT10_t* aht10 )
{
    char init = AHT10_SOFT_RESET;
    I2C_WriteByte( aht10->i2c , init );
}