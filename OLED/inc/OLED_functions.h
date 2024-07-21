#ifndef OLED_FUNCTIONS_H_
#define OLED_FUNCTIONS_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/ssi.h"
#include "big_heart.h"
#include "digits_bitmaps.h"
#include "OLED_functions.h"

#define SSD1351_WIDTH 96
#define SSD1351_HEIGHT 96
#define DIGIT_WIDTH 12
#define DIGIT_HEIGHT 12

#define COMMAND_DISPLAY_ON 0xAF
#define COMMAND_SHOW_RAM 0xA6
#define COMMAND_WRITE_RAM 0x5C
#define COMMAND_SET_COLUMN 0x75
#define COMMAND_SET_ROW 0x15
#define COMMAND_SET_COLUMN_INCREMENT 0xA0

#define RED_COLOR_PART1 0xF8
#define RED_COLOR_PART2 0x00
#define BLUE_COLOR_PART1 0xFF
#define BLUE_COLOR_PART2 0xFF
#define BLACK_COLOR_BOTH_PARTS 0x00
#define DISPLAY_COLUMN_INDEX_START 0
#define DISPLAY_COLUMN_INDEX_END 95
#define DISPLAY_ROW_INDEX_START 16
#define DISPLAY_ROW_INDEX_END 111

#define FIRST_NUMBER_COLUMN_INDEX_START 12
#define FIRST_NUMBER_COLUMN_INDEX_END 23
#define FIRST_NUMBER_ROW_INDEX_START 20
#define FIRST_NUMBER_ROW_INDEX_END 31

#define SECOND_NUMBER_COLUMN_INDEX_START 12
#define SECOND_NUMBER_COLUMN_INDEX_END 23
#define SECOND_NUMBER_ROW_INDEX_START 33
#define SECOND_NUMBER_ROW_INDEX_END 44

#define THIRD_NUMBER_COLUMN_INDEX_START 12
#define THIRD_NUMBER_COLUMN_INDEX_END 23
#define THIRD_NUMBER_ROW_INDEX_START 46
#define THIRD_NUMBER_ROW_INDEX_END 57

#define FOURTH_NUMBER_COLUMN_INDEX_START 12
#define FOURTH_NUMBER_COLUMN_INDEX_END 23
#define FOURTH_NUMBER_ROW_INDEX_START 99
#define FOURTH_NUMBER_ROW_INDEX_END 110

#define FIFTH_NUMBER_COLUMN_INDEX_START 12
#define FIFTH_NUMBER_COLUMN_INDEX_END 23
#define FIFTH_NUMBER_ROW_INDEX_START 86
#define FIFTH_NUMBER_ROW_INDEX_END 97

#define SIXTH_NUMBER_COLUMN_INDEX_START 12
#define SIXTH_NUMBER_COLUMN_INDEX_END 23
#define SIXTH_NUMBER_ROW_INDEX_START 73
#define SIXTH_NUMBER_ROW_INDEX_END 84

#define ONE_SECOND 16000000
#define ONE_MILI_SECOND 16000
#define TWO_MILI_SECOND 32000
#define TWO_HUNDRED_FIFTY_MILI_SECOND 4000000

#define FIRST_DIGIT_FLAG 0
#define SECOND_DIGIT_FLAG 1
#define THIRD_DIGIT_FLAG 2
#define FOURTH_DIGIT_FLAG 3
#define FIFTH_DIGIT_FLAG 4
#define SIXTH_DIGIT_FLAG 5

#define CLEAR_FLAG 10

#define PERCENTAGE_FLAG 11

#define SPI_BITRATE 1000000
#define SPI_BITWIDTH 8

void SPI0Initialization();
void send_command(uint8_t command);
void send_data(uint8_t data);
void SSD1351_Init();
void display_heart();
void display_digit(const uint8_t (*scheme)[12], uint8_t digit_flag);
void write_digit_to_RAM(uint8_t digit, uint8_t digit_flag);

typedef struct
{
    uint8_t start_column;
    uint8_t end_column;
    uint8_t start_row;
    uint8_t end_row;
} positionParams_t;

#endif
