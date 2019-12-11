/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef UART_H
#define UART_H

/* Includes ------------------------------------------------------------------*/
#include "stm8s_uart4.h"
/* Prototype -----------------------------------------------------------------*/
void UART_init(void);
void utoa_builtin_div(uint16_t value, char *buffer, int ofset);
#endif /* UART_H */
