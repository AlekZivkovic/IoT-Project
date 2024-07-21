#ifndef ATDRIVER_INCLUDE_CIRCULAR_BUFFER_H_
#define ATDRIVER_INCLUDE_CIRCULAR_BUFFER_H_

#include <stdint.h>
#include <stdbool.h>

#define CBUFFER_T_SIZE 32

typedef volatile struct CBuffer_t *CBuffer_t;

enum CBuffer_t_index
{
    FRIST, LAST
};

CBuffer_t xCBufferInit(void);
void vCBufferAddElem(CBuffer_t ptr, uint8_t elem);
uint8_t ucCBufferGetElem(CBuffer_t ptr);
uint16_t usCBufferGetIndex(CBuffer_t ptr, enum CBuffer_t_index indx);
void vCBufferIncIndex(CBuffer_t ptr, enum CBuffer_t_index indx);
bool isCBufferEmpty(CBuffer_t ptr);

#endif
