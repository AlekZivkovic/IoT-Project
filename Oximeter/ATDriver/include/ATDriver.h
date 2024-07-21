#ifndef ATDRIVER_INCLUDE_ATDRIVER_H_
#define ATDRIVER_INCLUDE_ATDRIVER_H_

#include <stdint.h>
#include <stdbool.h>

#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"

#include "ATDriver/include/Trie.h"

void ATDriver_init(uint8_t read_task_priority, QueueHandle_t SPO2_buffer_handle, QueueHandle_t HR_buffer_handle);
void ATDriverUARTISR(void);
bool bATDSend(uint8_t data, const char* topic);
bool isATDrivierInitFinished(void);

/* Should not be used */
extern TrieNode *cmdTrie;
extern QueueHandle_t pSPO2_buffer;
extern QueueHandle_t pHR_buffer;

#define MAX_SEMPH_SIZE 16
extern SemaphoreHandle_t readTaskSemaphore;

extern SemaphoreHandle_t validCmdResponse;
#define ASSERT_OK() (xSemaphoreTake(validCmdResponse, pdMS_TO_TICKS(2000)) == pdTRUE ? 1 : 0)

void vReadTask(void *pvParameters);
void vESPSetUpTask(void *pvParameters);


#endif
