
/* Includes ------------------------------------------------------------------*/
#include "GPIO.h"
#include "stm8s_gpio.h"

void GPIO_init(void)
{
    /* Initialize LEDs mounted on the Eval board */
  myGPIO_Init(LED_GPIO_PORT, LED_GPIO_PINS, GPIO_MODE_OUT_PP_LOW_FAST);
  LED_GPIO_PORT->ODR &= (uint8_t)(~LED_GPIO_PINS);
  /*Initialize Outputs*/
  myGPIO_Init(GPIOA, BALANCING_1_PIN|DIVIDER_EN_PIN,  GPIO_MODE_OUT_PP_LOW_FAST);
  //GPIO_Init(DIVIDER_PORT,   DIVIDER_EN_PIN,  GPIO_MODE_OUT_PP_LOW_FAST);
  myGPIO_Init(GPIOD, BALANCING_2_PIN|UART_TX_PIN,     GPIO_MODE_OUT_PP_LOW_FAST);
  myGPIO_Init(GPIOC, BALANCING_3_PIN|BALANCING_4_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
  //GPIO_Init(BALANCING_4_PORT, BALANCING_4_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
  /*-----------*/
  
  /*Initialize Inputs*/
  myGPIO_Init(GPIOD, GPIO_PIN_2|GPIO_PIN_3|UART_RX_PIN, GPIO_MODE_IN_FL_NO_IT);
  myGPIO_Init(GPIOB, GPIO_PIN_0|GPIO_PIN_1,             GPIO_MODE_IN_FL_NO_IT);
  myGPIO_Init(GPIOC, GPIO_PIN_4,                        GPIO_MODE_IN_FL_NO_IT);
  /*-----------*/
  GPIOA->ODR |= (uint8_t)DIVIDER_EN_PIN;
  

}

void myGPIO_Init(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef GPIO_Pin, GPIO_Mode_TypeDef GPIO_Mode)
{ 
  /* Reset corresponding bit to GPIO_Pin in CR2 register */
  GPIOx->CR2 &= (uint8_t)(~(GPIO_Pin));
  
  /*-----------------------------*/
  /* Input/Output mode selection */
  /*-----------------------------*/
  
  if ((((uint8_t)(GPIO_Mode)) & (uint8_t)0x80) != (uint8_t)0x00) /* Output mode */
  {
    if ((((uint8_t)(GPIO_Mode)) & (uint8_t)0x10) != (uint8_t)0x00) /* High level */
    {
      GPIOx->ODR |= (uint8_t)GPIO_Pin;
    } 
    else /* Low level */
    {
      GPIOx->ODR &= (uint8_t)(~(GPIO_Pin));
    }
    /* Set Output mode */
    GPIOx->DDR |= (uint8_t)GPIO_Pin;
  } 
  else /* Input mode */
  {
    /* Set Input mode */
    GPIOx->DDR &= (uint8_t)(~(GPIO_Pin));
  }
  
  /*------------------------------------------------------------------------*/
  /* Pull-Up/Float (Input) or Push-Pull/Open-Drain (Output) modes selection */
  /*------------------------------------------------------------------------*/
  
  if ((((uint8_t)(GPIO_Mode)) & (uint8_t)0x40) != (uint8_t)0x00) /* Pull-Up or Push-Pull */
  {
    GPIOx->CR1 |= (uint8_t)GPIO_Pin;
  } 
  else /* Float or Open-Drain */
  {
    GPIOx->CR1 &= (uint8_t)(~(GPIO_Pin));
  }
  
  /*-----------------------------------------------------*/
  /* Interrupt (Input) or Slope (Output) modes selection */
  /*-----------------------------------------------------*/
  
  if ((((uint8_t)(GPIO_Mode)) & (uint8_t)0x20) != (uint8_t)0x00) /* Interrupt or Slow slope */
  {
    GPIOx->CR2 |= (uint8_t)GPIO_Pin;
  } 
  else /* No external interrupt or No slope control */
  {
    GPIOx->CR2 &= (uint8_t)(~(GPIO_Pin));
  }
}