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

void main(void)
{
  CLK_init();  
  GPIO_init();
  ADC_init();
  UART_init();
  Adrecc_init();
  //Remap_init();
  //Priority_init();
  


  while (1)
  {
    //testADC_Value();
    //testADC_Filtr();
    //testADC_Measurement();
    Read_ADCval();
  }
}

