
/* Includes ------------------------------------------------------------------*/
#include "Flash.h"
#include "Service.h"
#include "stm8s_flash.h"
extern system_TYPE system;

void Adrecc_init(void)
{
  if(FLASH_ReadByte(ADDR_id_be)!=0x1)
  {
    system.ID_MCU=FLASH_ReadByte(ADDR_ID);
  }
  else
  {
    /*ID not be*/
  }
 
 /*write EEPROM--*/
// FLASH_Unlock(FLASH_MEMTYPE_DATA);
// FLASH_ProgramByte(ADDR_ID, 1);//ADRESS
// Delay(0xFFFF); 
// FLASH_ProgramByte(ADDR_id_be, ID_DEVICE_BE);
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

