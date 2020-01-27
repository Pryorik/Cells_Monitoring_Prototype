
/* Includes ------------------------------------------------------------------*/
#include "Priority.h"


/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* INIT-----------------------------------------------------------------------*/

void Priority_init(void)
{
    disableInterrupts();
    /*Software priority*/
    ITC_SetSoftwarePriority(ITC_IRQ_ADC1,        ITC_PRIORITYLEVEL_1);
    ITC_SetSoftwarePriority(ITC_IRQ_TIM5_OVFTRI, ITC_PRIORITYLEVEL_1);
    ITC_SetSoftwarePriority(ITC_IRQ_UART4_TX,    ITC_PRIORITYLEVEL_2);
    ITC_SetSoftwarePriority(ITC_IRQ_UART4_RX,    ITC_PRIORITYLEVEL_3);//need top priority for stability recive data
    
    enableInterrupts();
}

void _ITC_SetSoftwarePriority(ITC_Irq_TypeDef IrqNum, ITC_PriorityLevel_TypeDef PriorityValue)
{
  uint8_t Mask = 0;
  uint8_t NewPriority = 0;
  
  /* Define the mask corresponding to the bits position in the SPR register */
  /* The mask is reversed in order to clear the 2 bits after more easily */
  Mask = (uint8_t)(~(uint8_t)(0x03U << (((uint8_t)IrqNum % 4U) * 2U)));
  
  /* Define the new priority to write */
  NewPriority = (uint8_t)((uint8_t)(PriorityValue) << (((uint8_t)IrqNum % 4U) * 2U));
  
  switch (IrqNum)
  {
  case ITC_IRQ_UART4_TX:
  case ITC_IRQ_UART4_RX:
    ITC->ISPR5 &= Mask;
    ITC->ISPR5 |= NewPriority;
    break;    
  case ITC_IRQ_ADC1:
    ITC->ISPR6 &= Mask;
    ITC->ISPR6 |= NewPriority;
    break;
  default:
    break;
  }
}