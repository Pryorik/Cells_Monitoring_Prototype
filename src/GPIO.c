
/* Includes ------------------------------------------------------------------*/
#include "GPIO.h"
#include "stm8s_gpio.h"

void GPIO_init(void)
{
  /* Initialize LEDs mounted on the Eval board */
  GPIO_Init(LED_GPIO_PORT, LED_GPIO_PINS, GPIO_MODE_OUT_PP_LOW_FAST);
}
