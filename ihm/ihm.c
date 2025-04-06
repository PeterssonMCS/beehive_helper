#include "ihm.h"
#include "hal_def.h"

typedef enum
{
    PAGE_BEE = 0,
    PAGE_CONFIG,
    PAGE_RUN
}PAGES_t;

typedef enum
{
    APIS,
    URUCU,
    JATAI
}OPTION_t;

typedef enum{
    JOY_IDLE,
    BUTTON_A_PRESSED,
    BUTTON_B_PRESSED,
    JOY_UP,
    JOY_DOWN,
    JOY_RIGHT,
    JOY_LEFT,
    JOY_PRESSED
}INPUTS_STATE_t;

typedef struct
{
    INPUTS_STATE_t state;
}INPUTS_t;

INPUTS_t input;
PAGES_t page = 0;
OPTION_t option = 0;

const uint8_t limits[3][4] = { { 50 , 70 , 20 , 25 } , { 50 , 70 , 25 , 30 } , { 0 , 100 , 0 , 100 } };

extern const uint8_t bee_y[];
extern const uint8_t bee_x[];

static void PAGE_ConfigBees();
static void PAGE_Running();
static void PAGE_Bee();

void IHM_Init()
{
    D1306_Clear( GET_POINTER(D1306,OLED) );
    PAGE_Bee();
}

void IHM_Task()
{
    switch( page )
    {
        case PAGE_BEE:
            if( OS_GetTimeStamp() > 5000 )
            {
                page = PAGE_CONFIG;
            }
        break;
        case PAGE_CONFIG:
            D1306_Clear( GET_POINTER(D1306,OLED) );
            PAGE_ConfigBees();
        break;
        case PAGE_RUN:
            D1306_Clear( GET_POINTER(D1306,OLED) );
            PAGE_Running();
        break;
    }
}

void IHM_ProcessInput()
{
    JOYSTICK_Update(GET_POINTER(JOYSTICK,JOYSTICK));
    BUTTON_Update(GET_POINTER(BUTTON,BUTTON_A));
    BUTTON_Update(GET_POINTER(BUTTON,BUTTON_B));

    if( !BUTTON_GetState(GET_POINTER(BUTTON,BUTTON_A)))
    {
        input.state = BUTTON_A_PRESSED;
    }else if ( !BUTTON_GetState(GET_POINTER(BUTTON,BUTTON_B)))
    {
        input.state = BUTTON_B_PRESSED;
    }
    else if( JOYSTICK_GetX( GET_POINTER(JOYSTICK,JOYSTICK) ) > 230 )
    {
        input.state = JOY_RIGHT;
    }else if ( JOYSTICK_GetX( GET_POINTER(JOYSTICK,JOYSTICK) ) < 20 )
    {
        input.state = JOY_LEFT;
    }else if ( JOYSTICK_GetY( GET_POINTER(JOYSTICK,JOYSTICK) ) > 230 )
    {
        input.state = JOY_UP;
    }else if ( JOYSTICK_GetY( GET_POINTER(JOYSTICK,JOYSTICK) ) < 20 )
    {
        input.state = JOY_DOWN;
    }else if ( ! JOYSTICK_GetZ( GET_POINTER(JOYSTICK,JOYSTICK) ))
    {
        input.state = JOY_PRESSED;
    }else
    {
        input.state = JOY_IDLE;
    }
}

static void PAGE_ConfigBees()
{
    D1306_DrawString( GET_POINTER(D1306,OLED) , 0 , 0 , 1 , "Selecione Especie");
    D1306_DrawString( GET_POINTER(D1306,OLED) , 20 , 16 , 1 , "Apis Mellifera"); 
    D1306_DrawString( GET_POINTER(D1306,OLED) , 20 , 32 , 1 , "Urucu");
    D1306_DrawString( GET_POINTER(D1306,OLED) , 20 , 48 , 1 , "Jatai");
    D1306_DrawString( GET_POINTER(D1306,OLED) , 100 , 58 , 1 , "Avancar");
    
    LED_SetColor( GET_POINTER( LED , RGB ) , 0 , 0 , 0 );
    GPIO_SetOutput( GET_POINTER( GPIO , COOLER ) , 0 );

    switch( input.state )
    {
        case BUTTON_B_PRESSED:
            page = PAGE_RUN;
        break;
        case JOY_UP:
            option = option > APIS ? option - 1 : JATAI;
        break;
        case JOY_DOWN:
            option = option < JATAI ? option + 1 : APIS ;
        break;
        default:
        break;
    }

    switch( option )
    {
        case APIS:
            D1306_DrawSquare( GET_POINTER(D1306,OLED) , 12 , 19 , 2, 2);
        break;
        case URUCU:
            D1306_DrawSquare( GET_POINTER(D1306,OLED) , 12 , 35 , 2, 2);
        break;
        case JATAI:
            D1306_DrawSquare( GET_POINTER(D1306,OLED) , 12 , 51 , 2, 2);
        break;
    }
}

static void PAGE_Running()
{
    static char str_temp[12];
    static char str_humi[12];
    uint8_t temp = AHT10_GetTemperature( GET_POINTER(AHT10,SENSOR) );
    uint8_t humi = AHT10_GetHumidity( GET_POINTER(AHT10,SENSOR) );
    
    bool status_temp, status_humi;

    sprintf( str_temp,"Temp : %d", temp );
    sprintf( str_humi,"Humi : %d", humi );

    D1306_DrawString( GET_POINTER(D1306,OLED) , 0 , 0 , 1 , str_temp );
    D1306_DrawString( GET_POINTER(D1306,OLED) , 0 , 16 , 1 , str_humi );
    D1306_DrawString( GET_POINTER(D1306,OLED) , 0 , 54 , 1 , "Voltar");
    
    printf("%d,%d,%d,%d\n", limits[option][0] ,limits[option][1] ,limits[option][2] ,limits[option][3] );
    status_humi = ((humi > limits[option][0]) && (humi < limits[option][1])) ? 1 : 0;
    status_temp = ((temp > limits[option][2]) && (temp < limits[option][3])) ? 1 : 0;

    if( status_humi && status_temp )
    {
        LED_SetColor( GET_POINTER( LED , RGB ) , 0 , 0.5 , 0 );
        GPIO_SetOutput( GET_POINTER( GPIO , COOLER ) , 0 );
        D1306_DrawString( GET_POINTER(D1306,OLED) , 0 , 32 , 1 , "Bees are happy");
    }else if( !status_humi && !status_temp )
    {
        LED_SetColor( GET_POINTER( LED , RGB ) , 0.5 , 0 , 0 );
        GPIO_SetOutput( GET_POINTER( GPIO , COOLER ) , 1 );
        D1306_DrawString( GET_POINTER(D1306,OLED) , 0 , 32 , 1 , "Bees are unhappy");
    }else
    {
        LED_SetColor( GET_POINTER( LED , RGB ) , 0.5 , 0.5 , 0 );
        GPIO_SetOutput( GET_POINTER( GPIO , COOLER ) , 0 );
        D1306_DrawString( GET_POINTER(D1306,OLED) , 0 , 32 , 1 , "Bees are confortable");
    }

    switch( input.state )
    {
        case BUTTON_A_PRESSED:
            page = PAGE_CONFIG;
        break;
        default:
        break;
    }
}

static void PAGE_Bee()
{
    for( int index = 0; index < 774 ; index++ )
    {
        D1306_DrawPixel( GET_POINTER(D1306,OLED) , bee_x[index] , bee_y[index] );
    }
}