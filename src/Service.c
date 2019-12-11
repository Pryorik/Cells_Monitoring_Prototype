
/* Includes ------------------------------------------------------------------*/
#include "service.h"
#include "stm8s_adc1.h"
#include "UART.h"
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* INIT-----------------------------------------------------------------------*/
ADC ADC_Ch0={.val=0, .flag_update_val =0, .valAvg=0, .kmeasure=1024, .filtr = {.inc=0,.del=0,.flag_FilterReady=0,.flag_CalibrationOK=1,.sum=0,.Adc_old=0,.Adc_now=0}};
ADC ADC_Ch1={.val=0, .flag_update_val =0, .valAvg=0, .kmeasure=1024, .filtr = {.inc=0,.del=0,.flag_FilterReady=0,.flag_CalibrationOK=1,.sum=0,.Adc_old=0,.Adc_now=0}};
ADC ADC_Ch2={.val=0, .flag_update_val =0, .valAvg=0, .kmeasure=1024, .filtr = {.inc=0,.del=0,.flag_FilterReady=0,.flag_CalibrationOK=1,.sum=0,.Adc_old=0,.Adc_now=0}};
ADC ADC_Ch3={.val=0, .flag_update_val =0, .valAvg=0, .kmeasure=1024, .filtr = {.inc=0,.del=0,.flag_FilterReady=0,.flag_CalibrationOK=1,.sum=0,.Adc_old=0,.Adc_now=0}};
ADC ADC_Ch4={.val=0, .flag_update_val =0, .valAvg=0, .kmeasure=1024, .filtr = {.inc=0,.del=0,.flag_FilterReady=0,.flag_CalibrationOK=1,.sum=0,.Adc_old=0,.Adc_now=0}};

/**
* @brief  Read_ADCval.
**/
void Read_ADCval()
{
  if(ADC_Ch0.flag_update_val == 1)
  {
      ADC_Ch0.valAvg = filtr(ADC_Ch0.val,&ADC_Ch0.filtr);
      ADC_Ch0.flag_update_val = 0;
  }
  
  if(ADC_Ch1.flag_update_val == 1)
  {
      ADC_Ch1.valAvg = filtr(ADC_Ch1.val,&ADC_Ch1.filtr);
      ADC_Ch1.flag_update_val = 0;
  }
  
  if(ADC_Ch2.flag_update_val == 1)
  {
      ADC_Ch2.valAvg = filtr(ADC_Ch2.val,&ADC_Ch2.filtr);
      ADC_Ch2.flag_update_val = 0;
  }
  
  if(ADC_Ch3.flag_update_val == 1)
  {
      ADC_Ch3.valAvg = filtr(ADC_Ch3.val,&ADC_Ch3.filtr);
      ADC_Ch3.flag_update_val = 0;
       /*test ADCfiltr-----------------------------*/
      extern char TxBuffer[];
      utoa_builtin_div(ADC_Ch3.val,TxBuffer,0);
      utoa_builtin_div(ADC_Ch3.valAvg,TxBuffer,5);
      UART4_ITConfig(UART4_IT_TXE, ENABLE);
      /*-----------------------------test ADCfiltr*/
      
//    /*test measurement------------------------------*/
//    extern char TxBuffer[];
//    utoa_builtin_div(ADC_Ch3.val,TxBuffer,0);
//    utoa_builtin_div(measure(ADC_Ch3.val, ADC_Ch3.kmeasure), TxBuffer, 5);
//    UART4_ITConfig(UART4_IT_TXE, ENABLE);
//    /*-----------------------------test measurement*/
  }
  
  if(ADC_Ch4.flag_update_val == 1)
  {
      ADC_Ch4.valAvg = filtr(ADC_Ch4.val,&ADC_Ch4.filtr);
      ADC_Ch4.flag_update_val = 0;
  } 

}

/**
* @brief  measure.
**/
int16_t measure(uint16_t ADCavg, uint16_t kmeasure)
{
		if ((ADCavg <= 10))//32mV
		{ 
			return 0;
		}
		else
		{
			return (((uint32_t)ADCavg*3300) / kmeasure);
		}
}

/**
* @brief  filtr.
**/
uint16_t filtr(uint16_t ADCval, ADC_filtr *chx)
{
	chx->Adc_old = chx->ADCBuff[chx->inc];

	chx->ADCBuff[chx->inc] = ADCval;

	if (chx->del != SIZE_FILTR)
	{
		chx->del++;
	}
	else
	{
		chx->flag_FilterReady = 1;
		chx->sum = chx->sum - chx->Adc_old;
	}
	chx->sum = chx->sum + chx->ADCBuff[chx->inc];
	chx->inc++;
	if (chx->inc == SIZE_FILTR)
	{
		chx->inc = 0;
	}
	chx->Adc_now = chx->sum / chx->del;
        
        if(chx->flag_FilterReady == 1 && chx->flag_CalibrationOK == 0)
	{
		CalibrationSens(chx);
	}
        
	return chx->Adc_now;
}

/**
* @brief  CalibrationSens.
**/
void CalibrationSens(ADC_filtr *chx)
{
	if (chx->flag_FilterReady)
	{
        chx->flag_CalibrationOK = 1;
	}
}

/**
* @brief  GetValChannals.
**/
void GetValChannals(void)
{
        ADC_Ch0.val= ADC1_GetBufferValue(0);  //zero measuring point 
        ADC_Ch0.flag_update_val=1;
        ADC_Ch1.val= ADC1_GetBufferValue(1);  //battery one measuring point 
        ADC_Ch1.flag_update_val=1;  
        ADC_Ch2.val= ADC1_GetBufferValue(2);  //battery two measuring point 
        ADC_Ch2.flag_update_val=1;
        ADC_Ch3.val= ADC1_GetBufferValue(3);  //battery three measuring point 
        ADC_Ch3.flag_update_val=1;
        ADC_Ch4.val= ADC1_GetBufferValue(4);  //battery four measuring point 
        ADC_Ch4.flag_update_val=1;
        
        /*test ADC------------------------------*/
        //extern char TxBuffer[];
        //utoa_builtin_div(ADC_Ch3.val,TxBuffer,0);
        //utoa_builtin_div(ADC_Ch4.val,TxBuffer,5);
        //UART4_ITConfig(UART4_IT_TXE, ENABLE);
        /*-----------------------------test ADC*/
}