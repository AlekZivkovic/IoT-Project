#ifndef ATDRIVER_INCLUDE_UART_H_
#define ATDRIVER_INCLUDE_UART_H_

#include <stdint.h>
#include "ATDriver/include/circular_buffer.h"

extern CBuffer_t RBuffer;
extern CBuffer_t TBuffer;

void vUARTSensorRead(void);
void vUARTSensorSendCmd(const uint8_t*, uint32_t);
void UARTSensorConfig(void);

void vUARTConsoleSendv2(const uint8_t *val, uint32_t ctr);
void UARTConsoleConfig(void);

void UARTConfig(void);
#endif
