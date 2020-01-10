
/* Includes ------------------------------------------------------------------*/
#include "CLK.h"

void CLK_init(void)
{
  /* Initialization of the clock */
  /* Clock divider to HSI/1 */
  
  /* Clear High speed internal clock prescaler */
  CLK->CKDIVR &= (uint8_t)(~CLK_CKDIVR_HSIDIV);   //CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
  
  /* Set High speed internal clock prescaler */
  CLK->CKDIVR |= (uint8_t)CLK_PRESCALER_HSIDIV1;   //---------------------------------------------              
}
