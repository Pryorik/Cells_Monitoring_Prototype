
/* Includes ------------------------------------------------------------------*/
#include "Interrupt.h"
#include "service.h"
#include "stm8s_uart4.h"
#include "stm8s_adc1.h"
/* Private define ------------------------------------------------------------*/
#define TX_BUFFER_SIZE (countof(TxBuffer)-1)

/* Private macro -------------------------------------------------------------*/
#define countof(a)   (sizeof(a) / sizeof(*(a)))
/* Private variables ---------------------------------------------------------*/

char TxBuffer[] = "0000 0000\n\r";

INTERRUPT_HANDLER(UART4_TX_IRQHandler, 17)
{
    static uint8_t TxCounter = 0;
    /* Write one byte to the transmit data register */
    UART4_SendData8((uint8_t)TxBuffer[TxCounter++]);
    
     /* Loop until the end of transmission */
    while (UART4_GetFlagStatus(UART4_FLAG_TC) == RESET);
    
    if (TxCounter == TX_BUFFER_SIZE)
    {
      TxCounter=0;
      /* Disable the USART Transmit Complete interrupt */
      UART4_ITConfig(UART4_IT_TXE, DISABLE);
    }
  
}

INTERRUPT_HANDLER(UART4_RX_IRQHandler, 18)
{
  uint8_t temp;
  UART4->SR &= ~UART4_SR_RXNE;
  /* Read one byte from the receive data register and send it back */
  temp = (UART4_ReceiveData8() & 0x7F);
  UART4_SendData8(temp);
}

INTERRUPT_HANDLER(ADC1_IRQHandler, 22)
{
    /* Get converted value */
        ADC1_ClearITPendingBit(ADC1_IT_EOC);    /* Select the ADC1 channel */
        ADC1->CSR |= ADC1_CHANNEL_4; //scan 0 up 4 channel
        
        /* Get converted value scan continuous mode*/
        GetValChannals();
  
        /* Get converted value continuous mode*/
        //Conversion_Value = ADC1_GetConversionValue();
 }


