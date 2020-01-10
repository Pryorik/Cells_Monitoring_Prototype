
/* Includes ------------------------------------------------------------------*/
#include "Ring_Buffer.h"

void RING_Push(uint8_t  symbol, RING_buffer_t* buf)//valid
{
    buf->buffer[buf->idxIn++] = symbol;
    if (buf->idxIn >= buf->size) buf->idxIn = 0;
}

uint8_t RING_Pop(RING_buffer_t *buf)//valid
{
    uint8_t retval = buf->buffer[buf->idxOut++];
    if (buf->idxOut >= buf->size) buf->idxOut = 0;
    return retval;
}

uint16_t RING_GetCount(RING_buffer_t *buf)
{
    uint16_t retval = 0;
    if (buf->idxIn < buf->idxOut) retval = buf->size + buf->idxIn - buf->idxOut;
    else retval = buf->idxIn - buf->idxOut;
    return retval;
}

uint8_t RING_ShowSymbol(uint16_t symbolNumber ,RING_buffer_t *buf)
{
    uint32_t pointer = buf->idxOut + symbolNumber;
    //int32_t  retval = -1;
    uint8_t retval = 0;
    if (symbolNumber < RING_GetCount(buf))
    {
        if (pointer >= buf->size) pointer -= buf->size;
        retval = buf->buffer[ pointer ] ;
    }
    return retval;
}
void RING_Clear(RING_buffer_t* buf)
{
    buf->idxIn = 0;
    buf->idxOut = 0;
}
// void RING_Init(RING_buffer_t *buf, uint16_t size)
// {
//     buf->size = size;
//     buf->buffer = (uint8_t*) malloc(size);
//     RING_Clear(buf);
// }