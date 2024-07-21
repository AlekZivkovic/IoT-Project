#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

#include "ATDriver/include/circular_buffer.h"
#include "ATDriver/include/ATDriver.h"
#include "ATDriver/include/Trie.h"
#include "ATDriver/include/UART.h"
#include "ATDriverConfig.h"

const char* AT_RST ="AT+RST";
const char* AT_MODE = "AT+CWMODE=1";
const char* AT_CONNECT = "AT+CWJAP=\"" WIFI_SSID "\",\"" WIFI_PASSWORD "\"";
const char* AT_USER_CONFIG = "AT+MQTTUSERCFG=0,1,\"" MODULE_NAME "\",\"\",\"\",0,0,\"\"";
const char* AT_MQTTCONN = "AT+MQTTCONN=0,\"" IP_ADDRESS "\",1883,0";
const char* AT_MQTTSUB_SP02 = "AT+MQTTSUB=0,\"" SPO2_TOPIC_TX "\",1";
const char* AT_MQTTSUB_HR = "AT+MQTTSUB=0,\"" HR_TOPIC_TX "\",1";

static bool bATDriverState = false;
static SemaphoreHandle_t mATDriverState;

bool isATDrivierInitFinished(void){
    if(mATDriverState == NULL)
        return false;
    bool current;
    xSemaphoreTake(mATDriverState, portMAX_DELAY);
    current = bATDriverState;
    xSemaphoreGive(mATDriverState);
    return current;
}

void vESPSetUpTask(void *pvParameters)
{
    mATDriverState = xSemaphoreCreateMutex();

    vUARTSensorSendCmd((uint8_t*) AT_RST, strlen(AT_RST));
    ASSERT_OK();
    while(!ASSERT_OK()){
        vUARTSensorSendCmd((uint8_t*) AT_MODE, strlen(AT_MODE));
    }
    do{
        vUARTSensorSendCmd((uint8_t*) AT_CONNECT, strlen(AT_CONNECT));
    }while(!ASSERT_OK());
    do{
        vUARTSensorSendCmd((uint8_t*) AT_USER_CONFIG, strlen(AT_USER_CONFIG));
    }while(!ASSERT_OK());
    do{
        vUARTSensorSendCmd((uint8_t*) AT_MQTTCONN, strlen(AT_MQTTCONN));
    }while(!ASSERT_OK());
    do{
        vUARTSensorSendCmd((uint8_t*) AT_MQTTSUB_SP02, strlen(AT_MQTTSUB_SP02));
    }while(!ASSERT_OK());
    do{
        vUARTSensorSendCmd((uint8_t*) AT_MQTTSUB_HR, strlen(AT_MQTTSUB_HR));
    }while(!ASSERT_OK());

    xSemaphoreTake(mATDriverState, portMAX_DELAY);
    bATDriverState = true;
    xSemaphoreGive(mATDriverState);

    vTaskDelete(NULL);
}
