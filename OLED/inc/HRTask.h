#ifndef INC_HRTASK_H_
#define INC_HRTASK_H_

#include "FreeRTOS.h"
#include "queue.h"
#include <stdint.h>

#define HR_TASK_PRIORITY 3


void vHRTask(void *pvParameters);


extern QueueHandle_t HRqueue;


#endif
