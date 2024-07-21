#include "ReadMeasurementsTask.h"

void vMeasureTask(void *pvParameters)
{
    uint32_t start_millis;
    uint32_t current_millis;

    fifo_t raw_data;
    uint32_t counter;
    data_est raw_data_est;

    float ir_measures[SAMPLING_SIZE];
    float red_measures[SAMPLING_SIZE];
    uint32_t i;
    for (i = 0; i < SAMPLING_SIZE; i++)
    {
        ir_measures[i] = 0;
        red_measures[i] = 0;
    }

    data_est sum_data;
    uint32_t index = 0;
    data_est final_data;

    while (1)
    {
        start_millis = get_millis();
        raw_data_est.ir = 0;
        raw_data.raw_red = 0;
        counter = 0;
        do
        {
            raw_data = read_fifo();
            raw_data_est.ir += raw_data.raw_ir;
            raw_data_est.red += raw_data.raw_red;
            counter++;
            current_millis = get_millis();
        }
        while (current_millis < start_millis + T);

        raw_data_est.ir = raw_data_est.ir / counter;
        raw_data_est.red = raw_data_est.red / counter;

        sum_data.ir -= ir_measures[index];
        sum_data.red -= red_measures[index];

        sum_data.ir += raw_data_est.ir;
        sum_data.red += raw_data_est.red;

        ir_measures[index] = raw_data_est.ir;
        red_measures[index] = raw_data_est.red;

        final_data.ir = sum_data.ir / SAMPLING_SIZE;
        final_data.red = sum_data.red / SAMPLING_SIZE;

        xQueueSend(queue_data_est, (void* ) &final_data, portMAX_DELAY);
        
        index++;
        index %= SAMPLING_SIZE;
    }

}

fifo_t read_fifo(void)
{
    fifo_t raw_data;
    max30100_read_start(FIFO_DATA);
    uint8_t ir_15_8 = max30100_read_cont(FIFO_DATA);
    uint8_t ir_7_0 = max30100_read_cont(FIFO_DATA);
    uint8_t red_15_8 = max30100_read_cont(FIFO_DATA);
    uint8_t red_7_0 = max30100_read_stop(FIFO_DATA);

    raw_data.raw_ir = (((uint16_t)ir_15_8) << 8) | ir_7_0;
    raw_data.raw_red = (((uint16_t)red_15_8) << 8) | red_7_0;

    return raw_data;
}

