#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"

#include "ATDriver/include/ATDriver.h"
#include "ATDriverConfig.h"

#include "UpdateTask.h"
#include "ISR_common.h"
#include "millis.h"
#include "ReadMeasurementsTask.h"

volatile QueueHandle_t queue_data_est;

int main(void)
{

    SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_INT |
        SYSCTL_XTAL_16MHZ);

    i2c0_master_init();

    IntMasterEnable();

    init_millis();

    queue_data_est = xQueueCreate(RD_QUEUE_SIZE, sizeof(data_est));

    TimerHandle_t x_timer = xTimerCreate("MilisTimer", pdMS_TO_TICKS(1), pdTRUE,
                                         (void*) 0, vTimerCallback);

    xTimerStart(x_timer, 0);

    xTaskCreate(vUpdateTask, "PulseOxymeterUpdate", configMINIMAL_STACK_SIZE,
        NULL, UPDATE_TASK_PRIORITY, NULL);
    xTaskCreate(vMeasureTask, "MeasureTask", configMINIMAL_STACK_SIZE,
        NULL, UPDATE_TASK_PRIORITY, NULL);

    ATDriver_init(UPDATE_TASK_PRIORITY + 1, NULL, NULL);

    vTaskStartScheduler();

    for (;;);
}

