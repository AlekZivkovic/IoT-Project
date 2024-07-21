#ifndef INCLUDE_LISTENERTASK_H_
#define INCLUDE_LISTENERTASK_H_

#include "FreeRTOS.h"
#include "queue.h"

#define LISTENER_TASK_PRIORITY  (tskIDLE_PRIORITY + 1)
#define LISTENER_QUEUE_SIZE     16

typedef struct ListenerTaskParams{
    QueueHandle_t queue;
    const char* topic;
} ListenerTaskParams_t;


void vListenerTask(void *pvParameters);


#endif
