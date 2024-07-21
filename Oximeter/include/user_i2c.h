#ifndef USER_I2C_H_
#define USER_I2C_H_

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/i2c.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "inc/hw_memmap.h"
#include "driverlib/uart.h"
#include "driverlib/interrupt.h"
#include "inc/hw_ints.h"


void i2c0_master_init(void);
void i2c0_master_wait_and_check(void);
void i2c0_master_set_slave_adr(uint8_t ui8_slave_addr, bool b_receive);
void i2c0_master_data_put(uint8_t ui8_data, uint32_t ui32_cmd);
void i2c0_master_repeated_start(uint8_t ui8_slave_addr, bool b_receive);
uint8_t i2c0_master_data_get(uint32_t ui32_cmd);

#endif
