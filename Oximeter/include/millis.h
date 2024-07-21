#ifndef INCLUDE_MILLIS_H_
#define INCLUDE_MILLIS_H_

#include <stdint.h>

#include "FreeRTOS.h"
#include "semphr.h"

typedef struct
{
    uint32_t millis_count;
    SemaphoreHandle_t mutex;

} millis_counter_t;


void init_millis(void);

BaseType_t set_millis(uint32_t ul_count);

uint32_t get_millis(void);

#endif
