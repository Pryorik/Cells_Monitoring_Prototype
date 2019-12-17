/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SERVICE_H
#define SERVICE_H
/* DEFINES---------------------------------------------------------------------*/
#define  SIZE_FILTR 10
/* Includes -------------------------------------------------------------------*/
#include "stm8s.h"
/* Structure ------------------------------------------------------------------*/
typedef struct {
    uint8_t   inc;
    uint8_t   del;
    uint8_t   flag_FilterReady;
    uint8_t   flag_CalibrationOK;
    uint32_t  sum;
    uint16_t  Adc_old;
    uint16_t  ADCBuff[SIZE_FILTR];
    uint16_t  Adc_now;
}ADC_filtr;

typedef struct ADC{
    uint16_t val;
    uint8_t  flag_update_val;
    uint16_t valAvg;
    uint16_t kmeasure;
    ADC_filtr filtr;
}ADC;

typedef struct {
    uint16_t *ch0;
    uint16_t *ch1;
    uint16_t *ch2;
    uint16_t *ch3;
    uint16_t *ch4;
}ADCvalAvg;

typedef struct{
  unsigned int BalancingBattery1 : 1;
  unsigned int BalancingBattery2 : 1;
  unsigned int BalancingBattery3 : 1;
  unsigned int BalancingBattery4 : 1;  
  unsigned int EnableDvided : 1;
  unsigned int GAP : 3;
}Control_TYPE;

typedef struct {
  uint8_t ID_MCU;
  ADCvalAvg ValAvg;
  Control_TYPE Control;
}system_TYPE;

/* Prototype -----------------------------------------------------------------*/
int16_t measure(uint16_t ADCavg, uint16_t kmeasure);
uint16_t filtr(uint16_t ADCval, ADC_filtr *chx);
void CalibrationSens(ADC_filtr *chx);
void Read_ADCval(void);

#endif /* SERVICE_H */
