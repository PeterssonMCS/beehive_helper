#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void OS_Tick();

void OS_Run();

void OS_CreateTask( uint32_t , void(*)() );

void OS_CreateCounter( uint32_t , void(*)() );

uint32_t OS_GetTimeStamp();