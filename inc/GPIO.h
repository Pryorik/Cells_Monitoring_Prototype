/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef GPIO_H
#define GPIO_H

/* Includes ------------------------------------------------------------------*/

/* Prototype -----------------------------------------------------------------*/
void GPIO_init(void);

/* Define --------------------------------------------------------------------*/
#define LED_GPIO_PORT  (GPIOB)
#define LED_GPIO_PINS  (GPIO_PIN_5)

#endif /* GPIO_H */
