#include "millis.h"

static volatile millis_counter_t shared_millis;

void init_millis(void)
{
    shared_millis.millis_count = 0;
    shared_millis.mutex = xSemaphoreCreateMutex();
}

BaseType_t set_millis(uint32_t ul_count)
{
    xSemaphoreTakeFromISR(shared_millis.mutex, NULL);

    shared_millis.millis_count = ul_count;

    BaseType_t xTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(shared_millis.mutex, &xTaskWoken);
    return xTaskWoken;
}

uint32_t get_millis(void)
{
    uint32_t current_millis;
    xSemaphoreTake(shared_millis.mutex, portMAX_DELAY);
    current_millis = shared_millis.millis_count;
    xSemaphoreGive(shared_millis.mutex);

    return current_millis;
}
