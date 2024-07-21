#include <stdlib.h>

#include "ATDriver/include/circular_buffer.h"

struct CBuffer_t
{
    volatile uint16_t counter;
    volatile uint16_t first;
    volatile uint16_t last;
    volatile uint8_t buffer[CBUFFER_T_SIZE];
};

CBuffer_t xCBufferInit(void)
{
    CBuffer_t cbuff_l = malloc(sizeof(struct CBuffer_t));
    cbuff_l->counter = 0;
    cbuff_l->first = 0;
    cbuff_l->last = 0;

    return cbuff_l;
}

void vCBufferAddElem(CBuffer_t ptr, uint8_t elem)
{
    ptr->buffer[ptr->first] = elem;
    ptr->counter++;
    vCBufferIncIndex(ptr, FRIST);
}

uint8_t ucCBufferGetElem(CBuffer_t ptr)
{
    uint8_t val_l = ptr->buffer[ptr->last];
    ptr->counter--;
    vCBufferIncIndex(ptr, LAST);

    return val_l;
}

uint16_t usCBufferGetIndex(CBuffer_t ptr, enum CBuffer_t_index indx)
{
    return indx == FRIST ? ptr->first : ptr->last;
}

void vCBufferIncIndex(CBuffer_t ptr, enum CBuffer_t_index indx)
{
    volatile uint16_t *pindx_l = (indx == FRIST) ? &(ptr->first) : &(ptr->last);
    *pindx_l = (*pindx_l + 1) & (CBUFFER_T_SIZE - 1);
}

bool isCBufferEmpty(CBuffer_t ptr)
{
    return ptr->counter > 0 ? false : true;
}




