#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "driverlib/uart.h"
#include "driverlib/sysctl.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"

#include "ATDriverConfig.h"
#include "ATDriver/include/UART.h"
#include "ATDriver/include/circular_buffer.h"
#include "ATDriver/include/ATDriver.h"

CBuffer_t RBuffer = NULL;

void vUARTConsoleSendv2(const uint8_t *val, uint32_t ctr)
{
    while (ctr > 0)
    {
        volatile const uint8_t eg = *val;
        UARTCharPut(UART0_BASE, eg);
        val++;
        ctr--;
    }
}

void vUARTSensorRead(void)
{
    vCBufferAddElem(RBuffer, UARTCharGetNonBlocking(ATD_UART_BASE));
}

void vUARTSensorSendCmd(const uint8_t *val, uint32_t ctr)
{
    while (ctr > 0)
    {
        volatile const uint8_t eg = *val;
        UARTCharPut(ATD_UART_BASE, eg);
        val++;
        ctr--;
    }
    UARTCharPut(ATD_UART_BASE, '\r');
    UARTCharPut(ATD_UART_BASE, '\n');
}

static void vUint8ToStringHelper(uint8_t data)
{
    uint8_t divisor = 100;
    uint8_t digit;
    while ((data / divisor) == 0 && divisor > 1) {
        divisor /= 10;
    }

    do {
        digit = (data / divisor) % 10;
        UARTCharPut(ATD_UART_BASE, digit + '0');
        divisor /= 10;
    } while (divisor > 0);
}

bool bATDSend(uint8_t data, const char* topic)
{
    static char AT_SEND[AT_SEND_SIZE] = "AT+MQTTPUB=0,\"S\",\"D\",1,0";
    if(topic[0] != HR_TOPIC_TX[0] && topic[0] != SPO2_TOPIC_TX[0] &&
            topic[0] != HR_TOPIC_RX[0] && topic[0] != SPO2_TOPIC_RX[0])
        return false;
    if(!isATDrivierInitFinished())
        return false;

    uint8_t ch;
    uint8_t i = 0;

    for(; i < AT_SEND_SIZE;i++)
    {
        ch = AT_SEND[i];
        ch = ch == 'S' ? topic[0] : ch;
        if(ch == 'D')
            vUint8ToStringHelper(data);

        if(ch == '\0' || ch == 'D')
                 continue;
        UARTCharPut(ATD_UART_BASE, ch);
    }
    UARTCharPut(ATD_UART_BASE, '\r');
    UARTCharPut(ATD_UART_BASE, '\n');

    return ASSERT_OK();
}

void UARTConsoleConfig(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    SysCtlPeripheralSleepEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralSleepEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralClockGating(true);

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Configure the UART for 115,200, 8-N-1 operation.
    //
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                        UART_CONFIG_PAR_NONE));

    IntEnable(INT_UART0);
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
}

void UARTSensorConfig(void)
{
    SysCtlPeripheralEnable(ATD_SYSCTL_UART);
    SysCtlPeripheralEnable(ATD_SYSCTL_GPIO);

    SysCtlPeripheralSleepEnable(ATD_SYSCTL_UART);
    SysCtlPeripheralSleepEnable(ATD_SYSCTL_GPIO);
    SysCtlPeripheralClockGating(true);

    GPIOPinConfigure(ATD_UART_RX);
    GPIOPinConfigure(ATD_UART_TX);
    GPIOPinTypeUART(ATD_GPIO_BASE, ATD_GPIO_PIN);

    //
    // Configure the UART for 115,200, 8-N-1 operation.
    //
    UARTConfigSetExpClk(ATD_UART_BASE, SysCtlClockGet(), 115200,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                        UART_CONFIG_PAR_NONE));

    IntEnable(ATD_UART_INT);
    UARTIntEnable(ATD_UART_BASE, UART_INT_RX | UART_INT_RT);
    UARTEnable(ATD_UART_BASE);
}


void UARTConfig(void)
{
    RBuffer = xCBufferInit();

    UARTConsoleConfig();
    UARTSensorConfig();
}



