#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>


#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"

#include "ATDriver/include/ATDriver.h"
#include "ListenerTask.h"
#include "ATDriverConfig.h"

int main( void )
{

    SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_INT |
                           SYSCTL_XTAL_16MHZ);
    IntMasterEnable();
    QueueHandle_t HRQue = xQueueCreate(LISTENER_QUEUE_SIZE,sizeof(uint8_t));
    QueueHandle_t SPO2Que = xQueueCreate(LISTENER_QUEUE_SIZE,sizeof(uint8_t));

    ListenerTaskParams_t *HRTaskParam_t =
               (ListenerTaskParams_t *)pvPortMalloc(sizeof(ListenerTaskParams_t));
    HRTaskParam_t->queue = HRQue;
    HRTaskParam_t->topic = HR_TOPIC_RX;

    ListenerTaskParams_t *SPO2TaskParam_t =
            (ListenerTaskParams_t *)pvPortMalloc(sizeof(ListenerTaskParams_t));
    SPO2TaskParam_t->queue = SPO2Que;
    SPO2TaskParam_t->topic = SPO2_TOPIC_RX;


    xTaskCreate(vListenerTask, "HeartRateListener", configMINIMAL_STACK_SIZE,
                    HRTaskParam_t, LISTENER_TASK_PRIORITY, NULL);

    xTaskCreate(vListenerTask, "SPO2Listener", configMINIMAL_STACK_SIZE,
                    SPO2TaskParam_t, LISTENER_TASK_PRIORITY, NULL);
    ATDriver_init(LISTENER_TASK_PRIORITY+1, SPO2Que , HRQue);

    /* Start the tasks running. */
    vTaskStartScheduler();

     for( ;; );
}

