
/* Includes ------------------------------------------------------------------*/
#include "Flash.h"
#include "stm8s_flash.h"


void Adrecc_init(void)
{
 /*write EEPROM--*/
 FLASH_Unlock(FLASH_MEMTYPE_DATA);
 FLASH_ProgramByte(ADDR_ID, 1);//ADRESS
 Delay(0xFFFF); 
 FLASH_ProgramByte(ADDR_id_be, ID_DEVICE_BE);
}

void Remap_init(void)
{
   /*option bit AFR2*/
   if(FLASH_ReadByte(ADDR_OPT2)!=0x4)
   {
     FLASH_Unlock(FLASH_MEMTYPE_DATA);
     FLASH_ProgramOptionByte(ADDR_OPT2, 0x4);//AFR2 REMAP AIN2 AIN3
   }
}

