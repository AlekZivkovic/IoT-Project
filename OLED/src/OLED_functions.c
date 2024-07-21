#include "OLED_functions.h"

positionParams_t params[6] = { { FIRST_NUMBER_COLUMN_INDEX_START,
                                 FIRST_NUMBER_COLUMN_INDEX_END,
                                 FIRST_NUMBER_ROW_INDEX_START,
                                 FIRST_NUMBER_ROW_INDEX_END },
                               { SECOND_NUMBER_COLUMN_INDEX_START,
                               SECOND_NUMBER_COLUMN_INDEX_END,
                                 SECOND_NUMBER_ROW_INDEX_START,
                                 SECOND_NUMBER_ROW_INDEX_END },
                               { THIRD_NUMBER_COLUMN_INDEX_START,
                               THIRD_NUMBER_COLUMN_INDEX_END,
                                 THIRD_NUMBER_ROW_INDEX_START,
                                 THIRD_NUMBER_ROW_INDEX_END },
                               { FOURTH_NUMBER_COLUMN_INDEX_START,
                               FOURTH_NUMBER_COLUMN_INDEX_END,
                                 FOURTH_NUMBER_ROW_INDEX_START,
                                 FOURTH_NUMBER_ROW_INDEX_END },
                               { FIFTH_NUMBER_COLUMN_INDEX_START,
                               FIFTH_NUMBER_COLUMN_INDEX_END,
                                 FIFTH_NUMBER_ROW_INDEX_START,
                                 FIFTH_NUMBER_ROW_INDEX_END },
                               { SIXTH_NUMBER_COLUMN_INDEX_START,
                               SIXTH_NUMBER_COLUMN_INDEX_END,
                                 SIXTH_NUMBER_ROW_INDEX_START,
                                 SIXTH_NUMBER_ROW_INDEX_END } };

void SPI0Initialization()
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD))
    {
    }
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_SSI0))
    {
    }

    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA))
    {
    }
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_6);
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_7);
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_0);
    GPIOPinConfigure(GPIO_PA2_SSI0CLK);
    GPIOPinConfigure(GPIO_PA3_SSI0FSS);
    GPIOPinConfigure(GPIO_PA5_SSI0TX);
    GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_3 | GPIO_PIN_2);
    SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_3,
    SSI_MODE_MASTER,
                       SPI_BITRATE, SPI_BITWIDTH);
    SSIEnable(SSI0_BASE);
}

void send_command(uint8_t command)
{

    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, 0x00);
    SSIDataPutNonBlocking(SSI0_BASE, command);
    while (SSIBusy(SSI0_BASE))
        ;
}

void send_data(uint8_t data)
{

    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, GPIO_PIN_6);
    SSIDataPutNonBlocking(SSI0_BASE, data);
    while (SSIBusy(SSI0_BASE))
        ;

}

void SSD1351_Init()
{

    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, GPIO_PIN_7);
    SysCtlDelay(ONE_MILI_SECOND);
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, 0x00);
    SysCtlDelay(TWO_MILI_SECOND);
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, GPIO_PIN_7);
    SysCtlDelay(TWO_MILI_SECOND);
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, GPIO_PIN_0);
    SysCtlDelay(TWO_HUNDRED_FIFTY_MILI_SECOND);
}

void display_heart()
{
    send_command(COMMAND_SHOW_RAM);

    send_command(COMMAND_SET_COLUMN);
    send_data(DISPLAY_COLUMN_INDEX_START);
    send_data(DISPLAY_COLUMN_INDEX_END);

    send_command(COMMAND_SET_ROW);
    send_data(DISPLAY_ROW_INDEX_START);
    send_data(DISPLAY_ROW_INDEX_END);
    send_command(COMMAND_WRITE_RAM);
    int32_t j = 0;
    int32_t k = 0;
    for (j = 0; j < SSD1351_WIDTH; j++)
    {
        for (k = 0; k < SSD1351_WIDTH; k++)
        {
            if (big_heart[j][k])
            {
                send_data(RED_COLOR_PART1);
                send_data(RED_COLOR_PART2);

            }
            else
            {
                send_data(BLUE_COLOR_PART1);
                send_data(BLUE_COLOR_PART2);

            }
        }
    }
    send_command(COMMAND_DISPLAY_ON);

}

void display_digit(const uint8_t (*scheme)[12], uint8_t digit_flag)
{
    send_command(COMMAND_SET_COLUMN);
    send_data(params[digit_flag].start_column);
    send_data(params[digit_flag].end_column);

    send_command(COMMAND_SET_ROW);
    send_data(params[digit_flag].start_row);
    send_data(params[digit_flag].end_row);
    send_command(COMMAND_WRITE_RAM);
    int32_t j = 0;
    int32_t k = 0;
    for (j = 11; j >= 0; j--)
    {
        for (k = 11; k >= 0; k--)
        {
            if (scheme[j][k])
            {
                send_data(BLACK_COLOR_BOTH_PARTS);
                send_data(BLACK_COLOR_BOTH_PARTS);

            }
            else
            {
                send_data(BLUE_COLOR_PART1);
                send_data(BLUE_COLOR_PART2);

            }
        }
    }

}
void write_digit_to_RAM(uint8_t digit, uint8_t digit_flag)
{
    switch (digit)
    {
    case 0:
        display_digit(zero_digit, digit_flag);
        break;
    case 1:
        display_digit(one_digit, digit_flag);
        break;
    case 2:
        display_digit(two_digit, digit_flag);
        break;
    case 3:
        display_digit(three_digit, digit_flag);
        break;
    case 4:
        display_digit(four_digit, digit_flag);
        break;
    case 5:
        display_digit(five_digit, digit_flag);
        break;
    case 6:
        display_digit(six_digit, digit_flag);
        break;
    case 7:
        display_digit(seven_digit, digit_flag);
        break;
    case 8:
        display_digit(eight_digit, digit_flag);
        break;
    case 9:
        display_digit(nine_digit, digit_flag);
        break;
    case 10:
        display_digit(clear, digit_flag);
        break;
    case 11:
        display_digit(percetange, digit_flag);
        break;
    default:
        break;
    }

}
