#include "pOS.h"
#include <assert.h>

#define MAX_NUMBER_OF_TASKS 12

typedef struct 
{
    int id;
    uint32_t time_space;
    uint32_t last_activation;
    void (*callback)();
}TASK_t;

typedef struct
{
    uint32_t time_stamp;
    uint8_t number_of_tasks;
    TASK_t tasks[MAX_NUMBER_OF_TASKS];
}pOS_t;

pOS_t system_os = {
    .number_of_tasks = 0,
    .time_stamp = 0
};

void OS_Tick()
{
    system_os.time_stamp++;
}

uint32_t OS_GetTimeStamp()
{
    return system_os.time_stamp;
}

void OS_Run()
{
    for( int i = 0; i < system_os.number_of_tasks ; i++ )
    {
        if( system_os.time_stamp - system_os.tasks[i].last_activation >= system_os.tasks[i].time_space )
        {
            system_os.tasks[i].callback();
            system_os.tasks[i].last_activation = system_os.time_stamp; 
        }
    }
}

void OS_CreateTask( uint32_t time_space , void(*cb)() )
{
    assert( system_os.number_of_tasks < MAX_NUMBER_OF_TASKS );
    system_os.tasks[system_os.number_of_tasks].id = system_os.number_of_tasks;
    system_os.tasks[system_os.number_of_tasks].time_space = time_space;
    system_os.tasks[system_os.number_of_tasks].last_activation = system_os.time_stamp;
    system_os.tasks[system_os.number_of_tasks].callback = cb;
    system_os.number_of_tasks++;
}