/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "stm8s_gpio.h"
#include "stm8s_uart4.h"
#include "Service.h"

#include "UART.h"
#include "GPIO.h"
#include "CLK.h"
#include "ADC.h"
/*function prototypes -----------------------------------------------*/
void Delay(uint32_t nCount);

void main(void)
{
  CLK_init();  
  GPIO_init();
  UART_init();
  ADC_init();
 
  while (1)
  {
     /* Toggles LEDs */
    GPIO_WriteReverse(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PINS);
    Read_ADCval();
    Delay(0xFFFF); 
  }
}

/**                                                                                                                                                                                                                                     
  * @brief  Delay.
  * @param  nCount
  * @retval None
  */
void Delay(uint32_t nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}