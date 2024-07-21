#include "MAX30100.h"

void max30100_init(uint8_t int_enable_flag, uint8_t mode_config_flag,
                   uint8_t spo2_config_flag, uint8_t led_config_flag)
{
    max30100_write_start(INTERRUPT_ENABLE_REG);
    max30100_write_cont(int_enable_flag);
    max30100_fifo_reset();
    max30100_write_cont(mode_config_flag);
    max30100_write_cont(spo2_config_flag);
    max30100_write_cont(ZERO);
    max30100_write_stop(led_config_flag);

}

void max30100_read_start(uint8_t ui8_reg_adr)
{
    i2c0_master_set_slave_adr(MAX30100_I2C_ADDRESS, WRITE_TO_MAX30100_I2C);

    i2c0_master_data_put(ui8_reg_adr, I2C_MASTER_CMD_BURST_SEND_START);

    i2c0_master_repeated_start(MAX30100_I2C_ADDRESS, READ_FROM_MAX30100_I2C);
}

uint8_t max30100_read_cont()
{
    return i2c0_master_data_get(I2C_MASTER_CMD_BURST_SEND_START);
}

uint8_t max30100_read_stop()
{
    return i2c0_master_data_get(I2C_MASTER_CMD_BURST_SEND_STOP);
}

void max30100_write_start(uint8_t ui8_reg_adr)
{
    i2c0_master_set_slave_adr(MAX30100_I2C_ADDRESS, WRITE_TO_MAX30100_I2C);
    i2c0_master_data_put(ui8_reg_adr, I2C_MASTER_CMD_BURST_SEND_START);
}

void max30100_write_cont(uint8_t ui8_data)
{
    i2c0_master_data_put(ui8_data, I2C_MASTER_CMD_BURST_SEND_CONT);
}

void max30100_write_stop(uint8_t ui8_data)
{
    i2c0_master_data_put(ui8_data, I2C_MASTER_CMD_BURST_SEND_FINISH);
}

void max30100_fifo_reset()
{
    int i = 0;
    for (; i < 4; i++)
        i2c0_master_data_put(FIFO_RESET, I2C_MASTER_CMD_BURST_SEND_CONT);
}