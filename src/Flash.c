
/* Includes ------------------------------------------------------------------*/
#include "Flash.h"
#include "Service.h"
#include "stm8s_flash.h"
extern system_TYPE system;

void Adress_init(void)
{
  if(FLASH_ReadByte(ADDR_id_be)!=0x1)
  {
    system.ID_MCU=FLASH_ReadByte(ADDR_ID);
  }
  else
  {
    /*ID not be*/
  }
}

void Write_Adress(uint8_t ID)
{
   /*write EEPROM--*/
   //FLASH_Unlock(FLASH_MEMTYPE_DATA);
    /* Unlock data memory */
   FLASH->DUKR = FLASH_RASS_KEY2; /* Warning: keys are reversed on data memory !!! */
   FLASH->DUKR = FLASH_RASS_KEY1;
   
   FLASH_ProgramByte(ADDR_ID, ID);//ADRESS
   FLASH_WaitForLastOperation(FLASH_MEMTYPE_DATA);
   //Delay(0xFFFF); 
   FLASH_ProgramByte(ADDR_id_be, ID_DEVICE_BE);
}

void Remap_init(void)
{
   /*option bit AFR2*/
   if(FLASH_ReadByte(ADDR_OPT2)!=0x4)
   {
    //FLASH_Unlock(FLASH_MEMTYPE_DATA);
    /* Unlock data memory */
    FLASH->DUKR = FLASH_RASS_KEY2; /* Warning: keys are reversed on data memory !!! */
    FLASH->DUKR = FLASH_RASS_KEY1;
    
    //FLASH_ProgramOptionByte(ADDR_OPT2, 0x4);//AFR2 REMAP AIN2 AIN3
    /* Enable write access to option bytes */
    FLASH->CR2 |= FLASH_CR2_OPT;
    FLASH->NCR2 &= (uint8_t)(~FLASH_NCR2_NOPT);
    /* Program option byte and his complement */
    *((NEAR uint8_t*)ADDR_OPT2) = 0x4;
    *((NEAR uint8_t*)((uint16_t)(ADDR_OPT2 + 1))) = (uint8_t)(~0x4);
      FLASH_WaitForLastOperation(FLASH_MEMTYPE_PROG);
  
    /* Disable write access to option bytes */
    FLASH->CR2 &= (uint8_t)(~FLASH_CR2_OPT);
    FLASH->NCR2 |= FLASH_NCR2_NOPT;
   }
}

