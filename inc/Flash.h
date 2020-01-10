/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef FLASH_H
#define FLASH_H
/* DEFINES---------------------------------------------------------------------*/
#define ID_DEVICE_BE 0xAE
#define ADDR_id_be 0x4000
#define ADDR_ID 0x4001
#define ADDR_OPT2 0x4803
/* Includes -------------------------------------------------------------------*/
#include "stm8s.h"
/* Structure ------------------------------------------------------------------*/

/* Prototype -----------------------------------------------------------------*/
void Write_Adress(uint8_t ID);
void Adress_init(void);
void Remap_init(void);
#endif /* FLASH_H */
