
/* Includes ------------------------------------------------------------------*/
#include "UART.h"


void UART_init(void)
{
  //GPIO_Init(GPIOD, GPIO_PIN_6, GPIO_MODE_IN_PU_IT);
  GPIOD->DDR &= ~(1 << 6); //PC2 RX USART1 receive (????)
  GPIOD->DDR |= 1<<5; //PC3 TX USART1 transmit (?????)
  UART4_Init((uint32_t)115200,
             UART4_WORDLENGTH_8D,
             UART4_STOPBITS_1, 
             UART4_PARITY_NO,
             UART4_SYNCMODE_CLOCK_DISABLE, 
             UART4_MODE_TXRX_ENABLE);

  /* Enable the UART Receive interrupt: this interrupt is generated when the UART
    receive data register is not empty */
  UART4_ITConfig(UART4_IT_RXNE_OR, ENABLE);
  
  /* Enable the UART Transmit complete interrupt: this interrupt is generated 
     when the UART transmit Shift Register is empty */
  UART4_ITConfig(UART4_IT_TXE, ENABLE);

  /* Enable UART */
  UART4_Cmd(ENABLE);
  
    /* Enable general interrupts */
  enableInterrupts();
}


/*Writes four number"value" in string "buffer". 
"ofset" shifting relative to the zero element char* /
nominal ofset = 4*/
void utoa_builtin_div(uint16_t value, char *buffer, int ofset)
{
   int counterNUM=0;
   buffer += 4+ofset; 
   //*--buffer = 0;
   do
   {
      *--buffer = value % 10 + '0';
      value /= 10;
      counterNUM++;
   }
   while (value != 0);
   while (counterNUM<4)
   {
     *--buffer = 32;//ASCII SPACE
     counterNUM++;
   }
}
