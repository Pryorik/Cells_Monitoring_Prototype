
/* Includes ------------------------------------------------------------------*/
#include "Priority.h"

#include "stm8s_itc.h"
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* INIT-----------------------------------------------------------------------*/

void Priority_init(void)
{
    disableInterrupts();
    /*Software priority*/
    ITC_SetSoftwarePriority(ITC_IRQ_ADC1, ITC_PRIORITYLEVEL_2);
    ITC_SetSoftwarePriority(ITC_IRQ_UART4_TX, ITC_PRIORITYLEVEL_3);
    ITC_SetSoftwarePriority(ITC_IRQ_UART4_RX, ITC_PRIORITYLEVEL_3);
    enableInterrupts();
}