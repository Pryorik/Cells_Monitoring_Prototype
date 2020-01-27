/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef RING_BUFFER_H
#define RING_BUFFER_H


/* Includes ------------------------------------------------------------------*/
#include "stm8s_uart4.h"
typedef struct
{
    uint8_t *buffer;
    uint16_t idxIn;
    uint16_t idxOut;
    uint16_t size;
} RING_buffer_t;

//  volatile static uint16_t max_size_include = 0;
//  volatile uint16_t temp = 0;
//  temp = RING_GetCount(&RxRingBuf);
//  if(temp>max_size_include) max_size_include=temp;
  
#define RING_PUSH(fifosymbol,fifobuf)\
  {\
    fifobuf.buffer[fifobuf.idxIn++] = fifosymbol;\
    if (fifobuf.idxIn >= fifobuf.size) fifobuf.idxIn = 0;\
  }

//uint8_t retval = buf->buffer[buf->idxOut];  
#define RING_POP_inx(fifobuf)\
  {\
    fifobuf.idxOut++;\
    if (fifobuf.idxOut >= fifobuf.size) fifobuf.idxOut = 0;\
  }
  
//#define RING_GET_COUNT(buf)\
//  {\
//    if (buf.idxIn < buf.idxOut) (buf.size + buf.idxIn - buf.idxOut);\
//    else (buf.idxIn - buf.idxOut);\
//  }
/* Prototype -----------------------------------------------------------------*/
void RING_Push(uint8_t symbol, RING_buffer_t *buf);
uint8_t RING_Pop(RING_buffer_t *buf);
uint16_t RING_GetCount(RING_buffer_t *buf);
uint8_t RING_ShowSymbol(uint16_t symbolNumber ,RING_buffer_t *buf);
void RING_Clear(RING_buffer_t* buf);
//void RING_Init(RING_buffer_t *buf, uint16_t size);
#endif /* RING_BUFFER_H */
