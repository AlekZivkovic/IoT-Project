#ifndef INC_SPO2TASK_H_
#define INC_SPO2TASK_H_

#include "FreeRTOS.h"
#include "queue.h"
#include <stdint.h>

#define SPO2_TASK_PRIORITY 3


void vSPO2Task(void *pvParameters);


extern QueueHandle_t SPO2queue;


#endif /* INC_SPO2TASK_H_ */
