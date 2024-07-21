#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "SPO2Task.h"
#include "HRTask.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "ATDriver/include/ATDriver.h"
#include "ATDriverConfig.h"
#include "OLED_functions.h"


#define LISTENER_QUEUE_SIZE 16

QueueHandle_t SPO2queue=NULL;
QueueHandle_t HRqueue=NULL;

int main( void )
{

    SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_INT |
                           SYSCTL_XTAL_16MHZ);
    SPI0Initialization();
    SSD1351_Init();
    IntMasterEnable();
    HRqueue = xQueueCreate(LISTENER_QUEUE_SIZE,sizeof(uint8_t));
    SPO2queue = xQueueCreate(LISTENER_QUEUE_SIZE,sizeof(uint8_t));


    display_heart();


    xTaskCreate(vSPO2Task,"SPO2Task",configMINIMAL_STACK_SIZE,NULL,SPO2_TASK_PRIORITY,NULL);
    xTaskCreate(vHRTask,"HRTask",configMINIMAL_STACK_SIZE,NULL,HR_TASK_PRIORITY,NULL);
    ATDriver_init(4, SPO2queue , HRqueue);



    /* Start the tasks running. */
    vTaskStartScheduler();

     for( ;; );
}
