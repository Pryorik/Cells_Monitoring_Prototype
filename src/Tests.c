#include "Tests.h"

#include "Flash.h"
#include "Service.h"
#include "ADC.h"
#include "UART.h"
#include "GPIO.h"
#include "Ring_Buffer.h"
/* Includes ------------------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* INIT-----------------------------------------------------------------------*/
void testADC_Value(void)
{
        extern ADC ADC_Ch0;
        extern ADC ADC_Ch1;
        extern ADC ADC_Ch2;
        extern ADC ADC_Ch3;
        extern ADC ADC_Ch4;
        extern RING_buffer_t TxRingBuf; 
        
        char Out_Buffer[30];
        
        /*create string for transmission*/
        utoa_builtin_div(ADC_Ch0.val,Out_Buffer,0);
        Out_Buffer[4]=' ';
        utoa_builtin_div(ADC_Ch1.val,Out_Buffer,5);
        Out_Buffer[9]=' ';
        utoa_builtin_div(ADC_Ch2.val,Out_Buffer,10);
        Out_Buffer[14]=' ';
        utoa_builtin_div(ADC_Ch3.val,Out_Buffer,15);
        Out_Buffer[19]=' ';
        utoa_builtin_div(ADC_Ch4.val,Out_Buffer,20);
        Out_Buffer[24]='\n';
        Out_Buffer[25]='\r';
        
        for(int i=0;i<26;i++)
        {
          RING_Push((uint8_t)Out_Buffer[i],&TxRingBuf);
        }
        
        UART4_ITConfig(UART4_IT_TXE, ENABLE);
        
        Delay(0xFFFF); 
}

void testADC_Filtr(void)
{
        extern ADC ADC_Ch0;
        extern ADC ADC_Ch1;
        extern ADC ADC_Ch2;
        extern ADC ADC_Ch3;
        extern ADC ADC_Ch4;
        extern RING_buffer_t TxRingBuf; 
        
        char Out_Buffer[30];
        
        /*create string for transmission*/
        utoa_builtin_div(ADC_Ch0.valAvg,Out_Buffer,0);
//        Out_Buffer[4]='\n';
//        Out_Buffer[5]='\r';
        Out_Buffer[4]=' ';
        utoa_builtin_div(ADC_Ch1.valAvg,Out_Buffer,5);
        Out_Buffer[9]=' ';
        utoa_builtin_div(ADC_Ch2.valAvg,Out_Buffer,10);
        Out_Buffer[14]=' ';
        utoa_builtin_div(ADC_Ch3.valAvg,Out_Buffer,15);
        Out_Buffer[19]=' ';
        utoa_builtin_div(ADC_Ch4.valAvg,Out_Buffer,20);
        Out_Buffer[24]='\n';
        Out_Buffer[25]='\r';
        
//        SEND(Out_Buffer, 6);
          SEND(Out_Buffer, 26);
//        for(int i=0;i<26;i++)
//        {
//          RING_Push((uint8_t)Out_Buffer[i],&TxRingBuf);
//        }
//        
//        UART4_ITConfig(UART4_IT_TXE, ENABLE);
        
//        /*create string for transmission*/
//        utoa_builtin_div(ADC_Ch4.val,Out_Buffer,0);
//        Out_Buffer[4]=' ';
//        utoa_builtin_div(ADC_Ch4.valAvg,Out_Buffer,5);
//        Out_Buffer[9]='\n';
//        Out_Buffer[10]='\r';
//        
//        for(int i=0;i<11;i++)
//        {
//          RING_Push((uint8_t)Out_Buffer[i],&TxRingBuf);
//        }
//        
//        UART4_ITConfig(UART4_IT_TXE, ENABLE);
        
        Delay(0xFFFF); 
}

uint32_t Rup;
uint32_t Rdown;
void testADC_Measurement(void)
{
        extern ADC ADC_Ch0;
        extern ADC ADC_Ch1;
        extern ADC ADC_Ch2;
        extern ADC ADC_Ch3;
        extern ADC ADC_Ch4;
        extern RING_buffer_t TxRingBuf; 
        
        char Out_Buffer[30];
        
        /*create string for transmission*/
        ADC_Ch0.valAvg=11;
        utoa_builtin_div((((uint32_t)ADC_Ch0.valAvg*3300) / ADC_Ch0.kmeasure),Out_Buffer,0);
        Out_Buffer[4]=' ';
        
        Rup   = 1000;
        Rdown = 3600;
//        ADC_Ch0.valAvg=11;
//        ADC_Ch1.valAvg=943;
        utoa_builtin_div(measure(ADC_Ch1.valAvg, ADC_Ch1.kmeasure),Out_Buffer,5);
        Out_Buffer[9]=' ';
        utoa_builtin_div(measure(ADC_Ch2.valAvg, ADC_Ch2.kmeasure),Out_Buffer,10);
        Out_Buffer[14]=' ';
        utoa_builtin_div(measure(ADC_Ch3.valAvg, ADC_Ch3.kmeasure),Out_Buffer,15);
        Out_Buffer[19]=' ';
        utoa_builtin_div(measure(ADC_Ch4.valAvg, ADC_Ch4.kmeasure),Out_Buffer,20);
        Out_Buffer[24]='\n';
        Out_Buffer[25]='\r';
        
        for(int i=0;i<26;i++)
        {
          RING_Push((uint8_t)Out_Buffer[i],&TxRingBuf);
        }
        
//        utoa_builtin_div(ADC_Ch4.val,Out_Buffer,0);
//        Out_Buffer[4]=' ';
//        utoa_builtin_div(measure(ADC_Ch4.valAvg, ADC_Ch4.kmeasure), Out_Buffer, 5);
//        Out_Buffer[9]='\n';
//        Out_Buffer[10]='\r';
//        
//        for(int i=0;i<11;i++)
//        {
//          RING_Push((uint8_t)Out_Buffer[i],&TxRingBuf);
//        }
        
        UART4_ITConfig(UART4_IT_TXE, ENABLE);
        
        Delay(0xFFFF); 
}

void testLED(void)
{/* Toggles LEDs */
      GPIO_WriteReverse(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PINS);  
      //Delay(0xFFFF); 
}

/**
* @brief  measure.
**/
int16_t measure(uint32_t ADCavg, uint16_t kmeasure)
{
//		if ((ADCavg <= 10))//32mV
//		{ 
//			return 0;
//		}
//		else
//		{
//			return (((uint32_t)ADCavg*3300) / kmeasure);
//		}
  uint32_t val_ADC= (((ADCavg - ADC_Ch0.valAvg)*(Rup+Rdown))/Rdown) + ADC_Ch0.valAvg;
  return (((uint32_t)val_ADC*3300) / kmeasure);
}

/**                                                                                                                                                                                                                                     
  * @brief  Delay.
  * @param  nCount
  * @retval None
  */
#pragma optimize=none
void Delay(uint32_t nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}