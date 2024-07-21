#include "SPO2Task.h"
#include "OLED_functions.h"

void vSPO2Task(void *pvParameters)
{

    static uint8_t spo2 = 0;
    static uint8_t ones_digit = 0;
    static uint8_t tens_digit = 0;
    while (1)
    {
        while (xQueueReceive(SPO2queue,&spo2,portMAX_DELAY) != pdTRUE)
            ;
        ones_digit = spo2 % 10;
        tens_digit = (spo2 % 100) / 10;
        if (spo2 > 9)
        {
            write_digit_to_RAM(tens_digit, THIRD_DIGIT_FLAG);
            write_digit_to_RAM(ones_digit, SECOND_DIGIT_FLAG);
            write_digit_to_RAM(PERCENTAGE_FLAG, FIRST_DIGIT_FLAG);
        }
        else if (spo2 > 0)
        {
            write_digit_to_RAM(CLEAR_FLAG, THIRD_DIGIT_FLAG);
            write_digit_to_RAM(ones_digit, SECOND_DIGIT_FLAG);
            write_digit_to_RAM(PERCENTAGE_FLAG, FIRST_DIGIT_FLAG);
        }
        else
        {
            write_digit_to_RAM(CLEAR_FLAG, THIRD_DIGIT_FLAG);
            write_digit_to_RAM(CLEAR_FLAG, SECOND_DIGIT_FLAG);
            write_digit_to_RAM(CLEAR_FLAG, FIRST_DIGIT_FLAG);
        }

    }
}
