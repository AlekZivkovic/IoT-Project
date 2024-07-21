#include "HRTask.h"
#include "OLED_functions.h"

void vHRTask(void *pvParameters)
{

    static uint8_t hr = 0;
    static uint8_t ones_digit = 0;
    static uint8_t tens_digit = 0;
    static uint8_t hundred_digit = 0;
    while (1)
    {
        while (xQueueReceive(HRqueue,&hr,portMAX_DELAY) != pdTRUE)
            ;
        ones_digit = hr % 10;
        tens_digit = (hr % 100) / 10;
        hundred_digit = hr / 100;

        if (hr > 99)
        {
            write_digit_to_RAM(ones_digit, SIXTH_DIGIT_FLAG);
            write_digit_to_RAM(tens_digit, FIFTH_DIGIT_FLAG);
            write_digit_to_RAM(hundred_digit, FOURTH_DIGIT_FLAG);
        }
        else if (hr > 9)
        {
            write_digit_to_RAM(ones_digit, SIXTH_DIGIT_FLAG);
            write_digit_to_RAM(tens_digit, FIFTH_DIGIT_FLAG);
            write_digit_to_RAM(CLEAR_FLAG, FOURTH_DIGIT_FLAG);
        }
        else
        {
            if (hr == 0)
            {
                write_digit_to_RAM(CLEAR_FLAG, SIXTH_DIGIT_FLAG);
                write_digit_to_RAM(CLEAR_FLAG, FIFTH_DIGIT_FLAG);
                write_digit_to_RAM(CLEAR_FLAG, FOURTH_DIGIT_FLAG);
            }
            else
            {
                write_digit_to_RAM(ones_digit, SIXTH_DIGIT_FLAG);
                write_digit_to_RAM(CLEAR_FLAG, FIFTH_DIGIT_FLAG);
                write_digit_to_RAM(CLEAR_FLAG, FOURTH_DIGIT_FLAG);

            }
        }

//        write_digit_to_RAM(ones_digit, SIXTH_DIGIT_FLAG);
//        if (hr > 9)
//        {
//            write_digit_to_RAM(tens_digit, FIFTH_DIGIT_FLAG);
//        }
//        else
//        {
//            write_digit_to_RAM(CLEAR_FLAG, FIFTH_DIGIT_FLAG);
//        }
//        if (hr > 99)
//        {
//            write_digit_to_RAM(hundred_digit, FOURTH_DIGIT_FLAG);
//        }
//        else
//        {
//            write_digit_to_RAM(CLEAR_FLAG, FOURTH_DIGIT_FLAG);
//        }

    }
}

