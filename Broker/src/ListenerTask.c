#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

#include "ListenerTask.h"
#include "ATDriver/include/ATDriver.h"
#include "ATDriver/include/UART.h"

void vListenerTask(void *pvParameters) {
    ListenerTaskParams_t *params = (ListenerTaskParams_t *)pvParameters;
    QueueHandle_t queue = params->queue;
    const char *topic = params->topic;
    vPortFree(params);

    while(1){
        uint8_t dataToSend;
        while(xQueueReceive(queue, &dataToSend, portMAX_DELAY) != pdTRUE);

        bATDSend(dataToSend, topic);
    }
}

