#include "hal/hardware/gpio/gpio.h"
#include "hal/hardware/timer/timer.h"
#include "hal/hardware/spi/spi.h"
#include "hal/led/led.h"
#include "hal/buzzer/buzzer.h"
#include "hal/joystick/joystick.h"
#include "hal/display/driver1306.h"
#include "hal/button/button.h"
#include "hal/aht10/aht10.h"
#include "pOS.h"

#define PIN_LIST( MACRO )       \
    MACRO( RGB_RED , 13 )       \
    MACRO( RGB_GREEN , 11 )     \
    MACRO( RGB_BLUE , 12 )      \
    MACRO( SPI_TX , 19 )        \
    MACRO( SPI_RX , 16 )        \
    MACRO( SPI_CS , 17 )        \
    MACRO( SPI_CLK , 18 )       \
    MACRO( DISPLAY_SDA , 14 )   \
    MACRO( DISPLAY_SCL , 15 )   \
    MACRO( BUTTON_A , 5 )       \
    MACRO( BUTTON_B , 6 )       \
    MACRO( BUZZER_A , 10 )      \
    MACRO( BUZZER_B , 21 )      \
    MACRO( LED_MATRIX , 7 )     \
    MACRO( MICROPHONE , 28 )    \
    MACRO( JOYSTICK_X , 27 )    \
    MACRO( JOYSTICK_Y , 26 )    \
    MACRO( JOYSTICK_Z , 22 )    \
    MACRO( AHT10_SDA , 16 )     \
    MACRO( AHT10_SCL , 17 )     \
    MACRO( COOLER , 8 )         \
    MACRO( ALARM , 18 )


#define RESOURCES_LIST( MACRO ) \
    MACRO( TIMER )              \
    MACRO( LED )                \
    MACRO( BUZZER )             \
    MACRO( JOYSTICK )           \
    MACRO( GPIO )               \
    MACRO( D1306 )              \
    MACRO( AHT10 )              \
    MACRO( BUTTON )

#define HAL_LIST( MACRO )       \
    MACRO( TIMER , OS )         \
    MACRO( AHT10 , SENSOR )     \
    MACRO( D1306 , OLED )       \
    MACRO( JOYSTICK , JOYSTICK )\
    MACRO( BUTTON, BUTTON_A )   \
    MACRO( BUTTON, BUTTON_B )   \
    MACRO( LED , RGB )          \
    MACRO( GPIO, COOLER )       \
    MACRO( GPIO, ALARM )        \
    MACRO( BUZZER , BUZZER_B )

typedef enum
{
    #define MACRO( NAME , PIN ) NAME##_ID,
    PIN_LIST( MACRO )
    #undef MACRO
    PIN_LIST_MAX
}PIN_LIST_ID_t;

typedef enum
{
    #define MACRO( TYPE , NAME ) TYPE##_##NAME##_ID,
    HAL_LIST(MACRO)
    #undef MACRO
}HAL_LIST_t;

#define GEN_CFG( NAME ) bool NAME##_GetConfig( int id , NAME##_CONFIG_t* cfg )
#define GEN_PROTO( NAME ) GEN_CFG( NAME );

#define HAL_INIT( TYPE , NAME )                                     \
    TYPE##_CONFIG_t TYPE##_##NAME##_CFG;                            \
    TYPE##_GetConfig( TYPE##_##NAME##_ID , & TYPE##_##NAME##_CFG ); \
    TYPE##_##NAME = TYPE##_Init( TYPE##_##NAME##_CFG );

#define GEN_VAR( TYPE , NAME ) TYPE##_t * TYPE##_##NAME;
#define VAR_FUNC( TYPE , NAME ) TYPE##_t * GetVar_##TYPE##_##NAME()
#define GET_VAR( TYPE , NAME ) VAR_FUNC( TYPE , NAME ) { return TYPE##_##NAME; }
#define VAR_PROTO( TYPE , NAME ) VAR_FUNC( TYPE , NAME );
#define GET_POINTER( TYPE , NAME ) GetVar_##TYPE##_##NAME()

RESOURCES_LIST(GEN_PROTO)
HAL_LIST(VAR_PROTO)

void HAL_Init();