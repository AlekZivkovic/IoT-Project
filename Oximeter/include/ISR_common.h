#ifndef INCLUDE_ISR_COMMON_H_
#define INCLUDE_ISR_COMMON_H_

#include "FreeRTOS.h"
#include "timers.h"

#include "millis.h"

void UART0IntHandler(void);
void UART3IntHandler(void);

void vTimerCallback(TimerHandle_t xTimer);

#endif
