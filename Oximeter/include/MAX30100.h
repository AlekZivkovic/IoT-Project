#ifndef INC_MAX30100_H_
#define INC_MAX30100_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "user_i2c.h"

//*****************************************************************************
//
// MAX30100 MACROS
//
//*****************************************************************************
#define MAX30100_I2C_ADDRESS        0x57

#define READ_FROM_MAX30100_I2C      true
#define WRITE_TO_MAX30100_I2C       false

#define ZERO                        0x00

//*****************************************************************************
//
// MAX30100 Interrupt Status Register
//
//*****************************************************************************
#define INTERRUPT_STATUS_REG        0x00

#define PWR_RDY                     0x01
#define A_FULL                      0x80
#define TEMP_RDY                    0x40
#define HR_RDY                      0x20
#define SPO2_RDY                    0x10

//*****************************************************************************
//
// MAX30100 Interrupt Enable Register
//
//*****************************************************************************
#define INTERRUPT_ENABLE_REG        0x01

#define ENB_A_FULL                  0x80
#define ENB_TEMP_RDY                0x40
#define ENB_HR_RDY                  0x20
#define ENB_SO2_RDY                 0x10

//*****************************************************************************
//
// MAX30100 FIFO Registers
//
//*****************************************************************************
#define FIFO_WR_PTR                 0x02
#define OVF_COUNTER                 0x03
#define FIFO_RD_PTR                 0x04
#define FIFO_DATA                   0x05

#define FIFO_RESET                  0x00

//*****************************************************************************
//
// MAX30100 Mode Configuration Register
//
//*****************************************************************************
#define MODE_CONFIG             0x06

#define SHUT_DOWN               0x80
#define RESET                   0x40
#define TEMP_EN                 0x08
#define MODE_HR_ONLY            0x02
#define MODE_HR_AND_SPO2        0x03

//*****************************************************************************
//
// MAX30100 SPO2 Configuration Register (LED pulse width micro sc)
//
//      LED_PW      pulse width       ADC resolution [bits]
//**********************************************************
//      0x00            200                13
//      0x01            400                14
//      0x02            800                15
//      0x03            1600               16
//
//*****************************************************************************
#define SPO2_CONFIG             0x07

#define SPO2_HI_RES_EN          0x40

#define SPO2_SR_50              0x00
#define SPO2_SR_100             0x04
#define SPO2_SR_167             0x08
#define SPO2_SR_200             0x0B
#define SPO2_SR_400             0x10
#define SPO2_SR_600             0x14
#define SPO2_SR_800             0x18
#define SPO2_SR_1000            0x1B

#define LED_PW_200              0x00
#define LED_PW_400              0x01
#define LED_PW_800              0x02
#define LED_PW_1600             0x03

//*****************************************************************************
//
// MAX30100 LED Configuration Register (LED current mA)
//
//      RED_PA      IR_PA       mA
//****************************************
//      0x00        0x00        0.0
//      0x10        0x01        4.4
//      0x20        0x02        7.6
//      0x30        0x03        11.0
//      0x40        0x04        14.2
//      0x50        0x05        17.4
//      0x60        0x06        20.8
//      0x70        0x07        24.0
//      0x80        0x08        27.1
//      0x90        0x09        30.6
//      0xA0        0x0A        33.8
//      0xB0        0x0B        37.0
//      0xC0        0x0C        40.2
//      0xD0        0x0D        43.6
//      0xE0        0x0E        46.8
//      0xF0        0x0F        50.0
//
//*****************************************************************************
#define LED_CONFIG              0x09

#define RED_PA_VAL              0x80
#define IR_PA_VAL               0x0F

//*****************************************************************************
//
// MAX30100 Temperature Registers
//
//*****************************************************************************
#define TEMP_INTEGER             0x16
#define TEMP_FRACTION            0x17

//*****************************************************************************
//
// MAX30100 PART ID Registers
//
//*****************************************************************************
#define REV_ID                  0xFE
#define PART_ID 0xFF            0xFF

//*****************************************************************************
//
// MAX30100 API
//
//*****************************************************************************


void max30100_init(uint8_t int_enable_flag, uint8_t mode_config_flag,
                   uint8_t spo2_config_flag, uint8_t led_config_flag);

void max30100_read_start(uint8_t ui8_reg_adr);
uint8_t max30100_read_cont();
uint8_t max30100_read_stop();

void max30100_write_start(uint8_t ui8_reg_adr);
void max30100_write_cont(uint8_t ui8_data);
void max30100_write_stop(uint8_t ui8_data);

void max30100_fifo_reset();

#endif
