
/* Includes ------------------------------------------------------------------*/
#include "UART.h"
#include "Ring_Buffer.h"
#include "Interrupt.h"

void UART_init(void)
{
//  UART4_Init((uint32_t)921600,
//             UART4_WORDLENGTH_8D,
//             UART4_STOPBITS_1, 
//             UART4_PARITY_NO,
//             UART4_SYNCMODE_CLOCK_DISABLE, 
//             UART4_MODE_TXRX_ENABLE);
  
  uint32_t BaudRate=921600;
  uint8_t BRR2_1 = 0, BRR2_2 = 0;
  uint32_t BaudRate_Mantissa = 0, BaudRate_Mantissa100 = 0;
  /* Clear the word length bit */
  UART4->CR1 &= (uint8_t)(~UART4_CR1_M);
  /* Set the word length bit according to UART4_WordLength value */
  UART4->CR1 |= (uint8_t)UART4_WORDLENGTH_8D; 
  
  /* Clear the STOP bits */
  UART4->CR3 &= (uint8_t)(~UART4_CR3_STOP);
  /* Set the STOP bits number according to UART4_StopBits value  */
  UART4->CR3 |= (uint8_t)UART4_STOPBITS_1; 
  
  /* Clear the Parity Control bit */
  UART4->CR1 &= (uint8_t)(~(UART4_CR1_PCEN | UART4_CR1_PS  ));
  /* Set the Parity Control bit to UART4_Parity value */
  UART4->CR1 |= (uint8_t)UART4_PARITY_NO;
  
  /* Clear the LSB mantissa of UART4DIV  */
  UART4->BRR1 &= (uint8_t)(~UART4_BRR1_DIVM);
  /* Clear the MSB mantissa of UART4DIV  */
  UART4->BRR2 &= (uint8_t)(~UART4_BRR2_DIVM);
  /* Clear the Fraction bits of UART4DIV */
  UART4->BRR2 &= (uint8_t)(~UART4_BRR2_DIVF);
  
  /* Set the UART4 BaudRates in BRR1 and BRR2 registers according to UART4_BaudRate value */
  BaudRate_Mantissa    = ((uint32_t)CLK_GetClockFreq() / (BaudRate << 4));
  BaudRate_Mantissa100 = (((uint32_t)CLK_GetClockFreq() * 100) / (BaudRate << 4));
  
  /* The fraction and MSB mantissa should be loaded in one step in the BRR2 register*/
  /* Set the fraction of UARTDIV  */
  BRR2_1 = (uint8_t)((uint8_t)(((BaudRate_Mantissa100 - (BaudRate_Mantissa * 100))
                                << 4) / 100) & (uint8_t)0x0F); 
  BRR2_2 = (uint8_t)((BaudRate_Mantissa >> 4) & (uint8_t)0xF0);
  
  UART4->BRR2 = (uint8_t)(BRR2_1 | BRR2_2);
  /* Set the LSB mantissa of UARTDIV  */
  UART4->BRR1 = (uint8_t)BaudRate_Mantissa;           
  
  /* Disable the Transmitter and Receiver before setting the LBCL, CPOL and CPHA bits */
  UART4->CR2 &= (uint8_t)~(UART4_CR2_TEN | UART4_CR2_REN);
  /* Clear the Clock Polarity, lock Phase, Last Bit Clock pulse */
  UART4->CR3 &= (uint8_t)~(UART4_CR3_CPOL | UART4_CR3_CPHA | UART4_CR3_LBCL);
  /* Set the Clock Polarity, lock Phase, Last Bit Clock pulse */
  UART4->CR3 |= (uint8_t)((uint8_t)UART4_SYNCMODE_CLOCK_DISABLE & (uint8_t)(UART4_CR3_CPOL | \
  UART4_CR3_CPHA | UART4_CR3_LBCL));
  
  /* Set the Transmitter Enable bit */
  UART4->CR2 |= (uint8_t)UART4_CR2_TEN;
  /* Set the Receiver Enable bit */
  UART4->CR2 |= (uint8_t)UART4_CR2_REN;
  /* Clear the Clock Enable bit */
  UART4->CR3 &= (uint8_t)(~UART4_CR3_CKEN); 
  
  
  /* Enable the UART Receive interrupt: this interrupt is generated when the UART
    receive data register is not empty */
        // UART4_ITConfig(UART4_IT_RXNE_OR, ENABLE); 
  uint8_t uartreg = 0, itpos = 0x00;
  /* Get the UART4 register index */
  uartreg = (uint8_t)((uint16_t)UART4_IT_RXNE_OR >> 0x08);
  /* Get the UART4 IT index */
  itpos = (uint8_t)((uint8_t)1 << (uint8_t)((uint8_t)UART4_IT_RXNE_OR & (uint8_t)0x0F));
  UART4->CR2 |= itpos;
  
  /* Enable the UART Transmit complete interrupt: this interrupt is generated 
     when the UART transmit Shift Register is empty */
  //UART4_ITConfig(UART4_IT_TXE, ENABLE);

  /* Enable UART */
      //UART4_Cmd(ENABLE);
  /* UART4 Enable */
  UART4->CR1 &= (uint8_t)(~UART4_CR1_UARTD);
  
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

void SEND(uint8_t *Buff, uint8_t AmountByteTX)
{
    
    
    extern RING_buffer_t TxRingBuf; 
    
    for(int i=0; i < AmountByteTX;i++)
    {
      RING_Push(Buff[i], &TxRingBuf); 
    }
    UART4->CR2|=(UART4_SR_TXE);

}