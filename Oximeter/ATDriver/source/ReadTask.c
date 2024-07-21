#include <stdint.h>

#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

#include "ATDriver/include/circular_buffer.h"
#include "ATDriver/include/ATDriver.h"
#include "ATDriver/include/Trie.h"
#include "ATDriver/include/UART.h"
#include "ATDriverConfig.h"


void vReadTask(void *pvParameters)
{
    uint8_t readCmd = NONE;
    TrieNode *cmdTrieRoot = cmdTrie;
    QueueHandle_t qhandle = NULL;
    while (1){
        while (xSemaphoreTake(readTaskSemaphore,portMAX_DELAY) != pdTRUE);
        char ch = ucCBufferGetElem(RBuffer);
        vUARTConsoleSendv2((uint8_t*)&ch, 1);

        if (readCmd == NONE){
            switch (ch){
                case '\n':
                case '\r':
                case ':':
                    readCmd = cmdTrie->command;
                    cmdTrie = cmdTrieRoot;
                    break;
                case '+':
                case 0x00:
                    cmdTrie = cmdTrieRoot;
                    break;
                default:
                   if (ch >= 'A' && ch <= 'Z' && cmdTrie->children[ch - 'A'] != NULL ) {
                       cmdTrie = cmdTrie->children[ch - 'A'];
                   } else {
                       cmdTrie = cmdTrieRoot;
                   }
            }
        }else{
            uint8_t receivedValue = 0;
            char type ='0';

            switch(readCmd){
                case OK:
                    readCmd = NONE;
                    cmdTrie = cmdTrieRoot;
                    xSemaphoreGive(validCmdResponse);
                    break;
                case RECEIVE:
                    // +MQTTSUBRECV:0,"T",msgSize,int_value
                    while(ch != '"'){
                        while (xSemaphoreTake(readTaskSemaphore, portMAX_DELAY) != pdTRUE);
                        ch = ucCBufferGetElem(RBuffer);
                    }

                    // Read type (SPO2 or HR)
                    while (xSemaphoreTake(readTaskSemaphore, portMAX_DELAY) != pdTRUE);
                    ch = ucCBufferGetElem(RBuffer);
                    type = ch;

                    // Skip characters (",msgSize,)
                    while (xSemaphoreTake(readTaskSemaphore, portMAX_DELAY) != pdTRUE);
                    ucCBufferGetElem(RBuffer);  // Skip "
                    while (xSemaphoreTake(readTaskSemaphore, portMAX_DELAY) != pdTRUE);
                    ucCBufferGetElem(RBuffer);  // Skip ,
                    while(ch != ','){      // Skip msgSize
                           while (xSemaphoreTake(readTaskSemaphore, portMAX_DELAY) != pdTRUE);
                          ch =ucCBufferGetElem(RBuffer);
                    }

                    // Read value
                    while (1) {
                        while (xSemaphoreTake(readTaskSemaphore, portMAX_DELAY) != pdTRUE);
                        ch = ucCBufferGetElem(RBuffer);

                        if (ch == '\r' || ch == '\n') {
                            break;
                        }
                        if (ch >= '0' && ch <= '9') {
                            receivedValue = receivedValue * 10 + (ch - '0');
                        } else {
                            break;
                        }
                    }
                    readCmd = NONE;
                    cmdTrie = cmdTrieRoot;
                    qhandle = type == HR_TOPIC_TX[0] || type == HR_TOPIC_RX[0] ? pHR_buffer : pSPO2_buffer;

                    vUARTConsoleSendv2((uint8_t*)&type, 1);
                    vUARTConsoleSendv2((uint8_t*)&" ", 1);
                    vUARTConsoleSendv2((uint8_t*)&receivedValue, 1);

                    if(qhandle != NULL)
                        xQueueSendToBack(qhandle, (void*)&receivedValue,portMAX_DELAY);
                    break;
            }
        }

    }
}

