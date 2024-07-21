#include "UpdateTask.h"
#include "ReadMeasurementsTask.h"
#include "ATDriver/include/UART.h"

extern volatile QueueHandle_t queue_data_est;

void send_to_led(uint8_t data, uint8_t *prev_data, const char *topic)
{

    if (data != *prev_data)
    {
        bATDSend(data, topic);
    }
    *prev_data = data;
}

void vUpdateTask(void *pvParameters)
{
    uint8_t prev_bpm = 0;
    uint8_t prev_spo2 = 0;

    float last_ir_data = 0;
    float prev_ir_data = 0;
    uint32_t rise_count = 0;
    bool rising = false;
    uint32_t delta[MEASURE_SIZE];
    uint32_t ind = 0;
    uint32_t last_beat;
    uint32_t bpm = 0;
    uint32_t i;

    float spo2 = 0;
    float ir_AC_value_sq_sum = 0;
    float red_AC_value_sq_sum = 0;
    uint16_t samples_count = 0;

     while (isATDrivierInitFinished() != true)
     {
        vTaskDelay(pdMS_TO_TICKS(15));
     }

    while (1)
    {
        data_est new_data;
        xQueueReceive(queue_data_est, &new_data, portMAX_DELAY);
        last_ir_data = new_data.ir;

        ir_AC_value_sq_sum += new_data.ir * new_data.ir;
        red_AC_value_sq_sum += new_data.red * new_data.red;
        samples_count++;

        if (last_ir_data > THRESHOLD_FINGER)
        {
            if (last_ir_data > prev_ir_data)
            {
                rise_count++;
                if (!rising && rise_count > THRESHOLD)
                {
                    rising = true;
                    delta[ind] = get_millis() - last_beat;
                    last_beat = get_millis();
                    uint32_t sum_delta = 0;
                    uint32_t counter = 0;
                    for (i = 1; i < MEASURE_SIZE; i++)
                    {
                        if ((delta[i] < delta[i - 1] * 1.1)
                                && (delta[i] > delta[i - 1] / 1.1))
                        {
                            counter++;
                            sum_delta += delta[i];
                        }
                    }
                    ind++;
                    ind %= MEASURE_SIZE;
                    bpm = MS_NUM / (sum_delta / counter);

                    if (bpm > BPM_LOW && bpm < BPM_HIGH)
                    {
                        send_to_led(bpm, &prev_bpm, HR_TOPIC_TX);
                    }

                    float ratio_RMS = log(
                            sqrt(red_AC_value_sq_sum / samples_count))
                            / log(sqrt(ir_AC_value_sq_sum / samples_count));
                    spo2 = 110.0 - 14.5 * ratio_RMS;

                    if (spo2 > SPO2_LOW && spo2 < SPO2_HIGH)
                    {
                        send_to_led(spo2, &prev_spo2, SPO2_TOPIC_TX);
                    }
                }
            }
            else
            {
                rise_count = 0;
                rising = false;
            }
            prev_ir_data = last_ir_data;
        }
        else
        {
            /***no finger on***/
            bpm = 0;
            spo2 = 0;
            send_to_led(bpm, &prev_bpm, HR_TOPIC_TX);
            send_to_led(spo2, &prev_spo2, SPO2_TOPIC_TX);
            prev_bpm = bpm;
            prev_spo2 = spo2;

        }
    }
}

