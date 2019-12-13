#include "Tests.h"

#include "Service.h"
#include "ADC.h"
#include "UART.h"
#include "GPIO.h"
/* Includes ------------------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* INIT-----------------------------------------------------------------------*/
void testADC_Value(void)
{
      extern char TxBuffer[];
      extern ADC ADC_Ch0;
      extern ADC ADC_Ch1;
      extern ADC ADC_Ch2;
      extern ADC ADC_Ch3;
      extern ADC ADC_Ch4;

      if( (UART4->CR2 & UART4_CR2_TIEN) == 0 )//if UART_DR empty
      {
            /*create string for transmission*/
            utoa_builtin_div(ADC_Ch0.val,TxBuffer,0);
            TxBuffer[4]=' ';
            utoa_builtin_div(ADC_Ch1.val,TxBuffer,5);
            TxBuffer[9]=' ';
            utoa_builtin_div(ADC_Ch2.val,TxBuffer,10);
            TxBuffer[14]=' ';
            utoa_builtin_div(ADC_Ch3.val,TxBuffer,15);
            TxBuffer[19]=' ';
            utoa_builtin_div(ADC_Ch4.val,TxBuffer,20);
            TxBuffer[24]='\n';
            TxBuffer[25]='\r';
            UART4_ITConfig(UART4_IT_TXE, ENABLE);
            Delay(0xFFFF); 
      }
}

void testADC_Filtr(void)
{
      extern char TxBuffer[];
      extern ADC ADC_Ch0;
      extern ADC ADC_Ch1;
      extern ADC ADC_Ch2;
      extern ADC ADC_Ch3;
      extern ADC ADC_Ch4;
      
      if( (UART4->CR2 & UART4_CR2_TIEN) == 0 )//if UART_DR empty
      {
          /*create string for transmission*/
          utoa_builtin_div(ADC_Ch4.val,TxBuffer,0);
          TxBuffer[4]=' ';
          utoa_builtin_div(ADC_Ch4.valAvg,TxBuffer,5);
          TxBuffer[9]='\n';
          TxBuffer[10]='\r';
          UART4_ITConfig(UART4_IT_TXE, ENABLE);
          Delay(0xFFFF); 
      }
}

void testADC_Measurement(void)
{
      extern char TxBuffer[];
      extern ADC ADC_Ch0;
      extern ADC ADC_Ch1;
      extern ADC ADC_Ch2;
      extern ADC ADC_Ch3;
      extern ADC ADC_Ch4;
      
      if( (UART4->CR2 & UART4_CR2_TIEN) == 0 )//if UART_DR empty
      {
          utoa_builtin_div(ADC_Ch4.val,TxBuffer,0);
          TxBuffer[4]=' ';
          utoa_builtin_div(measure(ADC_Ch4.valAvg, ADC_Ch4.kmeasure), TxBuffer, 5);
          TxBuffer[9]='\n';
          TxBuffer[10]='\r';
          UART4_ITConfig(UART4_IT_TXE, ENABLE);
          Delay(0xFFFF); 
      }
}

void testLED(void)
{/* Toggles LEDs */
      GPIO_WriteReverse(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PINS);  
      Delay(0xFFFF); 
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