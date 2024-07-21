#include <stdint.h>
#include <stdbool.h>

#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

#include "ATDriver/include/circular_buffer.h"
#include "ATDriver/include/ATDriver.h"
#include "ATDriver/include/Trie.h"
#include "ATDriver/include/UART.h"
#include  "ATDriverConfig.h"

#include "driverlib/uart.h"

TrieNode *cmdTrie = NULL;
QueueHandle_t pSPO2_buffer = NULL;
QueueHandle_t pHR_buffer = NULL;


#define MAX_SEMPH_SIZE 16
SemaphoreHandle_t readTaskSemaphore = NULL;

SemaphoreHandle_t validCmdResponse = NULL;

void ATDriverUARTISR(void)
{
    vUARTSensorRead();
    BaseType_t xTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(readTaskSemaphore, &xTaskWoken);
    portYIELD_FROM_ISR(xTaskWoken);
}

void Trie_init(void)
{
    cmdTrie = xTrieNodeCreateNode();

    vTrieNodeInsert(cmdTrie, "MQTTSUBRECV", RECEIVE);
    vTrieNodeInsert(cmdTrie, "OK", OK);
}

void ATDriver_init(uint8_t read_task_priority, QueueHandle_t SPO2_buffer_handle,
                   QueueHandle_t HR_buffer_handle)
{
    Trie_init();
    UARTConfig();
    readTaskSemaphore = xSemaphoreCreateCounting(MAX_SEMPH_SIZE, 0);
    validCmdResponse = xSemaphoreCreateCounting(1, 0);
    pSPO2_buffer = SPO2_buffer_handle;
    pHR_buffer = HR_buffer_handle;

    xTaskCreate(vReadTask, "ATDReadTask", configMINIMAL_STACK_SIZE, NULL,
                read_task_priority, NULL);
    xTaskCreate(vESPSetUpTask, "ATDESPSetUpTask", configMINIMAL_STACK_SIZE, NULL,
                    read_task_priority+1, NULL);
}
