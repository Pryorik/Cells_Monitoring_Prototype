/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"

#include "Service.h"
#include "UART.h"
#include "GPIO.h"
#include "CLK.h"
#include "ADC.h"
#include "Flash.h"
#include "Tests.h"
#include "Priority.h"
#include "Check_Tasks.h"
#include "stm8s_tim5.h"

void main(void)
{
  CLK_init();  
  GPIO_init();
  ADC_init();
  UART_init();
  Adress_init();
  Remap_init();
  Priority_init();
  TIM5_TimeBaseInit(TIM5_PRESCALER_16,(uint16_t)50);
  TIM5->CR1 |= TIM5_CR1_CEN;
  TIM5->IER |= (uint8_t)TIM5_IT_UPDATE;
  while (1)
  {
    //GPIOD->ODR &= (uint8_t)(~UART_TX_PIN);
    //GPIOD->ODR |= (uint8_t)(UART_TX_PIN);   
    //GPIOB->ODR &= (uint8_t)(~LED_GPIO_PINS);
    //GPIOB->ODR |= (uint8_t)(LED_GPIO_PINS);
    
   //testADC_Value();
   //testADC_Filtr();
   //testADC_Measurement();
   //testLED();
   Read_ADCval();
   
   // wfi();
  }
}

