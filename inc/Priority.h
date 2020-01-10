/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PRIORITY_H
#define PRIORITY_H
/* DEFINES---------------------------------------------------------------------*/
/* Includes -------------------------------------------------------------------*/
#include "stm8s_itc.h"
/* Structure ------------------------------------------------------------------*/

/* Prototype -----------------------------------------------------------------*/
void Priority_init(void);
void _ITC_SetSoftwarePriority(ITC_Irq_TypeDef IrqNum, ITC_PriorityLevel_TypeDef PriorityValue);
#endif /* PRIORITY_H */
