#ifndef INCLUDE_READ_MEASUREMENTS_TASK_H_
#define INCLUDE_READ_MEASUREMENT

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "millis.h"
#include "MAX30100.h"

#define RD_QUEUE_SIZE       16
#define SAMPLING_SIZE       4
#define T                   50
 
typedef struct raw_data_est
{
    float ir;
    float red;
} data_est;

typedef struct fifo_t
{
    uint16_t raw_ir;
    uint16_t raw_red;
} fifo_t;


void vMeasureTask(void *pvParameters);
fifo_t read_fifo(void);

extern volatile QueueHandle_t queue_data_est;

#endif 