
/* Includes ------------------------------------------------------------------*/
#include "ADC.h"
#include "stm8s_adc1.h"
/*Note
If the ADC is not used for a long time, it is recommended to switch it to power down mode to
decrease power consumption. This is done by clearing the ADON bit*/
void ADC_init(void)
{  
  /* De-Init ADC 8peripheral*/
  //ADC1_DeInit();
  ADC1->CSR  = ADC1_CSR_RESET_VALUE;
  ADC1->CR1  = ADC1_CR1_RESET_VALUE;
  ADC1->CR2  = ADC1_CR2_RESET_VALUE;
  ADC1->CR3  = ADC1_CR3_RESET_VALUE;
  ADC1->TDRH = ADC1_TDRH_RESET_VALUE;
  ADC1->TDRL = ADC1_TDRL_RESET_VALUE;
  ADC1->HTRH = ADC1_HTRH_RESET_VALUE;
  ADC1->HTRL = ADC1_HTRL_RESET_VALUE;
  ADC1->LTRH = ADC1_LTRH_RESET_VALUE;
  ADC1->LTRL = ADC1_LTRL_RESET_VALUE;
  ADC1->AWCRH = ADC1_AWCRH_RESET_VALUE;
  ADC1->AWCRL = ADC1_AWCRL_RESET_VALUE;
  
  /* Enable ADC1 SCAN MODE */
        //ADC1_ScanModeCmd(ENABLE);
  ADC1->CR2 |= ADC1_CR2_SCAN;
  
  /* Enable ADC1 Buffer */
        //ADC1_DataBufferCmd(ENABLE);
  ADC1->CR3 |= ADC1_CR3_DBUF;
  
  /* Enable EOC interrupt */
        //ADC1_ITConfig(ADC1_IT_EOCIE, ENABLE);
  ADC1->CSR |= (uint8_t)ADC1_IT_EOCIE;
  /* Enable general interrupts */  
  enableInterrupts();

  
        //  /* Init ADC1 peripheral */ 
        //  ADC1_Init (ADC1_CONVERSIONMODE_CONTINUOUS, 
        //            ADC1_CHANNEL_4,       // In scan mode it is mean that scaning chanell 0 to 4 
        //            ADC1_PRESSEL_FCPU_D18,
        //            ADC1_EXTTRIG_TIM, DISABLE, 
        //            ADC1_ALIGN_RIGHT, 
        //            ADC1_SCHMITTTRIG_CHANNEL0|ADC1_SCHMITTTRIG_CHANNEL1|ADC1_SCHMITTTRIG_CHANNEL2|ADC1_SCHMITTTRIG_CHANNEL3|ADC1_SCHMITTTRIG_CHANNEL4, DISABLE);
  
    /*-----------------CR1 & CSR configuration --------------------*/
  /* Configure the conversion mode and the channel to convert
  respectively according to ADC1_ConversionMode & ADC1_Channel values  &  ADC1_Align values */
                            //ADC1_ConversionConfig(ADC1_CONVERSIONMODE_CONTINUOUS, ADC1_CHANNEL_4, ADC1_ALIGN_RIGHT);
  /* Clear the align bit */
  ADC1->CR2 &= (uint8_t)(~ADC1_CR2_ALIGN);
  /* Configure the data alignment */
  ADC1->CR2 |= (uint8_t)(ADC1_ALIGN_RIGHT);
  /* Set the continuous conversion mode */
  ADC1->CR1 |= ADC1_CR1_CONT;
    /* Clear the ADC1 channels */
  ADC1->CSR &= (uint8_t)(~ADC1_CSR_CH);
  /* Select the ADC1 channel */
  ADC1->CSR |= (uint8_t)(ADC1_CHANNEL_4);
  
  /* Select the prescaler division factor according to ADC1_PrescalerSelection values */
                            // ADC1_PrescalerConfig(ADC1_PRESSEL_FCPU_D18);
  /* Clear the SPSEL bits */
  ADC1->CR1 &= (uint8_t)(~ADC1_CR1_SPSEL);
  /* Select the prescaler division factor according to ADC1_PrescalerSelection values */
  ADC1->CR1 |= (uint8_t)(ADC1_PRESSEL_FCPU_D18);
  
  /*-----------------CR2 configuration --------------------*/
  /* Configure the external trigger state and event respectively
  according to NewState, ADC1_ExtTrigger */
                          //ADC1_ExternalTriggerConfig(ADC1_EXTTRIG_TIM, DISABLE);
  /* Clear the external trigger selection bits */
  ADC1->CR2 &= (uint8_t)(~ADC1_CR2_EXTSEL);
  /* Disable the selected external trigger */
  ADC1->CR2 &= (uint8_t)(~ADC1_CR2_EXTTRIG);
  /* Set the selected external trigger */
  ADC1->CR2 |= (uint8_t)(ADC1_EXTTRIG_TIM);
  
  /*------------------TDR configuration ---------------------------*/
  /* Configure the schmitt trigger channel and state respectively
  according to ADC1_SchmittTriggerChannel & ADC1_SchmittTriggerNewState  values */
                        //ADC1_SchmittTriggerConfig((ADC1_SCHMITTTRIG_CHANNEL0|ADC1_SCHMITTTRIG_CHANNEL1|ADC1_SCHMITTTRIG_CHANNEL2|ADC1_SCHMITTTRIG_CHANNEL3|ADC1_SCHMITTTRIG_CHANNEL4), DISABLE);
  ADC1->TDRL |= (uint8_t)((uint8_t)0x01 << (uint8_t)(ADC1_SCHMITTTRIG_CHANNEL0|ADC1_SCHMITTTRIG_CHANNEL1|ADC1_SCHMITTTRIG_CHANNEL2|ADC1_SCHMITTTRIG_CHANNEL3|ADC1_SCHMITTTRIG_CHANNEL4));
  
  
  
  /* Enable the ADC1 peripheral */
  ADC1->CR1 |= ADC1_CR1_ADON;
  
  /*Start Conversion */
  ADC1_StartConversion();//double command!! may be clear
}
