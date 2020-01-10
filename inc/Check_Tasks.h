/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef CHECK_TASKS_H
#define CHECK_TASKS_H
/* DEFINES---------------------------------------------------------------------*/
#define  ALL_ID 0x1F
enum Commands_MCU_ID{
SEND_MEASUREMENTS = 0x1,
BALLANCING_B1     = 0x2,
BALLANCING_B2     = 0x3,
BALLANCING_B3     = 0x4,
BALLANCING_B4     = 0x5
};

enum Commands_ALL_ID{
Get_ID            = 0x3
};

enum ERROR{
  ERROR_CRC                 = 0x1
};
/* Includes -------------------------------------------------------------------*/
#include "stm8s.h"
#include "Ring_Buffer.h"

/* Structure ------------------------------------------------------------------*/
typedef struct {
  uint8_t Command;
  uint8_t ID;
  uint8_t AmoundByte;
  uint8_t BuffPackage[9];
  uint8_t ERROR;
}parsing;
/* Prototype -----------------------------------------------------------------*/
void Check_Tasks(void);
parsing Parsing_RX_Package(RING_buffer_t *Buff);
uint8_t FoundCRC(uint8_t *Buff, uint8_t AmoundByte);
uint8_t pack_DATA_ADC(uint8_t Comand_and_ID, uint8_t *Buf);
#endif /* CHECK_TASKS_H */
