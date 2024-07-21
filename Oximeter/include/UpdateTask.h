#ifndef INCLUDE_UPDATE_TASK_H_
#define INCLUDE_UPDATE_TASK_H_

#include <stdbool.h>
#include <stdint.h>

#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

#include "ATDriver/include/ATDriver.h"
#include "ATDriver/include/UART.h"
#include "ATDriverConfig.h"

#define UPDATE_TASK_PRIORITY  (tskIDLE_PRIORITY + 1)
#define MEASURE_SIZE            10
#define THRESHOLD               3
#define THRESHOLD_FINGER        10000
#define BPM_LOW                 40
#define BPM_HIGH                220
#define MS_NUM                  60000

#define SPO2_LOW                 88
#define SPO2_HIGH                100

void send_to_led(uint8_t data, uint8_t *prev_data, const char *topic);
void vUpdateTask(void *pvParameters);

#endif