
/* Includes ------------------------------------------------------------------*/
#include "ADC.h"
#include "stm8s_adc1.h"
/*Note
If the ADC is not used for a long time, it is recommended to switch it to power down mode to
decrease power consumption. This is done by clearing the ADON bit*/
void ADC_init(void)
{
  /*  Init GPIO for ADC1 */
  GPIO_Init(GPIOD, GPIO_PIN_3|GPIO_PIN_2, GPIO_MODE_IN_FL_NO_IT);
  /* De-Init ADC 8peripheral*/
  ADC1_DeInit();
  
  /* Enable ADC1 SCAN MODE */
  ADC1_ScanModeCmd(ENABLE);
  
  /* Enable ADC1 Buffer */
  ADC1_DataBufferCmd(ENABLE);
  
      /* Enable EOC interrupt */
  ADC1_ITConfig(ADC1_IT_EOCIE, ENABLE);

  /* Enable general interrupts */  
  enableInterrupts();

  
  /* Init ADC1 peripheral */ 
  ADC1_Init (ADC1_CONVERSIONMODE_CONTINUOUS, 
            ADC1_CHANNEL_4,       // In scan mode it is mean that scaning chanell 0 to 4 
            ADC1_PRESSEL_FCPU_D18,
            ADC1_EXTTRIG_TIM, DISABLE, 
            ADC1_ALIGN_RIGHT, 
            ADC1_SCHMITTTRIG_ALL, DISABLE);
  /*Start Conversion */
  ADC1_StartConversion();//double command!! may be clear
}


