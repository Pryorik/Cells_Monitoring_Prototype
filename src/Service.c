
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

system_TYPE system = {.ID_MCU=0, .ValAvg = {.ch0=&ADC_Ch0.valAvg, .ch1=&ADC_Ch1.valAvg, .ch2=&ADC_Ch2.valAvg, .ch3=&ADC_Ch3.valAvg, .ch4=&ADC_Ch4.valAvg}, .Control={0}};

/**
* @brief  Read_ADCval.
**/
void Read_ADCval(void)
{
  if(ADC_Ch0.flag_update_val == 1)
  {
      //ADC_Ch0.valAvg=2;
      ADC_Ch0.valAvg = filtr(ADC_Ch0.val,&ADC_Ch0.filtr);
      ADC_Ch0.flag_update_val = 0;
  }
  
  if(ADC_Ch1.flag_update_val == 1)
  {
      //ADC_Ch1.valAvg=3;
      ADC_Ch1.valAvg = filtr(ADC_Ch1.val,&ADC_Ch1.filtr);
      ADC_Ch1.flag_update_val = 0;
  }
  
  if(ADC_Ch2.flag_update_val == 1)
  {
      //ADC_Ch2.valAvg=4;
      ADC_Ch2.valAvg = filtr(ADC_Ch2.val,&ADC_Ch2.filtr);
      ADC_Ch2.flag_update_val = 0;
  }
  
  if(ADC_Ch3.flag_update_val == 1)
  {
      //ADC_Ch3.valAvg=5;
      ADC_Ch3.valAvg = filtr(ADC_Ch3.val,&ADC_Ch3.filtr);
      ADC_Ch3.flag_update_val = 0;
  }
  
  if(ADC_Ch4.flag_update_val == 1)
  {
      //ADC_Ch4.valAvg=6;
      ADC_Ch4.valAvg = filtr(ADC_Ch4.val,&ADC_Ch4.filtr);
      ADC_Ch4.flag_update_val = 0;
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
        
//        if(chx->flag_FilterReady == 1 && chx->flag_CalibrationOK == 0)
//	{
//		CalibrationSens(chx);
//	}
        
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

