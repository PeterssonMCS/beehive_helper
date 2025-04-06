#include <stdio.h>
#include "pico/stdlib.h"
#include "hal_def.h"
#include "ihm/ihm.h"

void Task_Sensor()
{
    //While the sensor is busy reading don't update the value
    if( ! AHT10_ReadStatus( GET_POINTER(AHT10,SENSOR) ) )
    {
        AHT10_Update( GET_POINTER(AHT10,SENSOR) );
        AHT10_TriggerMeasurement( GET_POINTER(AHT10,SENSOR) );
    }
}

void Task_IHM()
{
    IHM_Task();
}

void Task_Input()
{
    IHM_ProcessInput();
}

void Task_Display()
{
    D1306_Show( GET_POINTER(D1306,OLED) );
}

void Task_Alarm()
{
    if( !GPIO_GetInput(GET_POINTER(GPIO,ALARM)))
    {
        printf("alarm on\n");
        BUZZER_Enable( GET_POINTER(BUZZER,BUZZER_B) );
    }else
    {
        printf("alarm off\n");
        BUZZER_Disable( GET_POINTER(BUZZER,BUZZER_B) );
    }
}

int main()
{
    stdio_init_all();

    HAL_Init();

    IHM_Init();
    
    OS_CreateTask( 2000 , Task_Sensor );
    OS_CreateTask( 100 , Task_Input );
    OS_CreateTask( 100 , Task_IHM );
    OS_CreateTask( 100 , Task_Display );
    OS_CreateTask( 10000 , Task_Alarm );

    while(1)
    {
        OS_Run();
    };
}
