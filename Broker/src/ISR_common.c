#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/uart.h"
#include "driverlib/interrupt.h"

#include "ISR_common.h"
#include "ATDriver/include/ATDriver.h"

void UART0IntHandler(void)
{
    uint32_t ui32Status;
    ui32Status = UARTIntStatus(UART0_BASE, true);
    UARTIntClear(UART0_BASE, ui32Status);
    ATDriverUARTISR();
}

void UART3IntHandler(void)
{
    uint32_t ui32Status;
    ui32Status = UARTIntStatus(UART3_BASE, true);
    UARTIntClear(UART3_BASE, ui32Status);
    ATDriverUARTISR();
}
