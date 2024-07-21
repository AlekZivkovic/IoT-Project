#include "user_i2c.h"

void i2c0_master_init(void)
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_I2C0))
    {
    }

    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB))
    {
    }

    GPIOPinConfigure(GPIO_PB2_I2C0SCL);
    GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
    GPIOPinConfigure(GPIO_PB3_I2C0SDA);
    GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);

    IntDisable(INT_I2C0);
    I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), false);
}

void i2c0_master_set_slave_adr(uint8_t ui8_slave_addr, bool b_receive)
{
    I2CMasterSlaveAddrSet(I2C0_BASE, ui8_slave_addr, b_receive);
    i2c0_master_wait_and_check();
}

void i2c0_master_wait_and_check()
{
    while (I2CMasterBusy(I2C0_BASE))
        ;
    if (I2CMasterErr(I2C0_BASE) != I2C_MASTER_ERR_NONE)
    {
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_ERROR_STOP);
    }
}

void i2c0_master_data_put(uint8_t ui8_data, uint32_t ui32_cmd)
{
    I2CMasterDataPut(I2C0_BASE, ui8_data);
    I2CMasterControl(I2C0_BASE, ui32_cmd);
    i2c0_master_wait_and_check();
}

void i2c0_master_repeated_start(uint8_t ui8_slave_addr, bool b_receive)
{
    I2CMasterSlaveAddrSet(I2C0_BASE, ui8_slave_addr, b_receive);
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);
    i2c0_master_wait_and_check();
}

uint8_t i2c0_master_data_get(uint32_t ui32_cmd)
{
    uint8_t data = I2CMasterDataGet(I2C0_BASE);
    I2CMasterControl(I2C0_BASE, ui32_cmd);
    i2c0_master_wait_and_check();
    return data;
}
