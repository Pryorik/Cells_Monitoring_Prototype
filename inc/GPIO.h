/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef GPIO_H
#define GPIO_H

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
/* Prototype -----------------------------------------------------------------*/
void myGPIO_Init(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef GPIO_Pin, GPIO_Mode_TypeDef GPIO_Mode);
/* Define --------------------------------------------------------------------*/
#define LED_GPIO_PORT  (GPIOB)
#define LED_GPIO_PINS  (GPIO_PIN_4)

#define BALANCING_1_PORT (GPIOA)// DIVIDER_EN_PORT
#define BALANCING_1_PIN  (GPIO_PIN_2)

#define BALANCING_2_PORT (GPIOD)
#define BALANCING_2_PIN  (GPIO_PIN_4)

#define BALANCING_3_PORT (GPIOC)
#define BALANCING_3_PIN  (GPIO_PIN_5)

#define BALANCING_4_PORT (GPIOC)
#define BALANCING_4_PIN  (GPIO_PIN_6)

#define DIVIDER_PORT     (GPIOA)
#define DIVIDER_EN_PIN   (GPIO_PIN_1)

#define UART_TX_PIN      (GPIO_PIN_5)
#define UART_RX_PIN      (GPIO_PIN_6)

#endif /* GPIO_H */
