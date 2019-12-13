/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef TESTS_H
#define TESTS_H
/* DEFINES---------------------------------------------------------------------*/
/* Includes -------------------------------------------------------------------*/
#include "stm8s.h"
/* Structure ------------------------------------------------------------------*/

/* Prototype -----------------------------------------------------------------*/
void testADC_Value(void);
void testADC_Filtr(void);
void testADC_Measurement(void);
void Delay(uint32_t nCount);
void testLED(void);

#endif /* TESTS_H */
