
/* Includes ------------------------------------------------------------------*/
#include "Interrupt.h"
#include "service.h"
#include "stm8s_uart4.h"
#include "stm8s_adc1.h"
/* Private define ------------------------------------------------------------*/
//define TX_BUFFER_SIZE (countof(TxBuffer)-1)
#define RX_BUFFER_SIZE 20 //1ComADD+Am+DATA7+1CRS = 9 + spare 11byte
/* Private macro -------------------------------------------------------------*/
//#define countof(a)   (sizeof(a) / sizeof(*(a)))

/* variables ---------------------------------------------------------*/
//char    TxBuffer[TX_BUFFER_SIZE];
uint8_t RXBuffer[RX_BUFFER_SIZE];


uint32_t ValueClearCSR=0x20+ADC1_CHANNEL_4;


//INTERRUPT_HANDLER(UART4_TX_IRQHandler, 17)
//{
//    static uint8_t TxCounter = 0;
//        
//    /* Write one byte to the transmit data register */
//    UART4_SendData8((uint8_t)TxBuffer[TxCounter]);
//    
//    TxCounter++;  
//    /*software clear TXEmpty*/
//    UART4->SR &= ~UART4_SR_TXE;
//    
//    if(TxBuffer[TxCounter-1]=='\r')
//    {
//      TxCounter=0;
//      /* Disable the USART Transmit Complete interrupt */
//      UART4_ITConfig(UART4_IT_TXE, DISABLE);
//    }
//}
uint8_t *TXBuff_ptr;
uint8_t AmountByteTX=0;
INTERRUPT_HANDLER(UART4_TX_IRQHandler, 17)
{
    static uint8_t TxCounter = 0;
    
    /* Write one byte to the transmit data register */
    UART4_SendData8((uint8_t)*(TXBuff_ptr+TxCounter));
    
    TxCounter++;  
    /*software clear TXEmpty*/
    UART4->SR &= ~UART4_SR_TXE;
    
    if((TxCounter) == AmountByteTX)
    {
      TxCounter=0;
      /* Disable the USART Transmit Complete interrupt */
      UART4_ITConfig(UART4_IT_TXE, DISABLE);
    }
}


uint8_t flag_package_ready=0;
uint8_t AmountByteRX=0;
uint8_t RxCounter = 0;
INTERRUPT_HANDLER(UART4_RX_IRQHandler, 18)
{/*[8bit Command_and_Addr]+[8bit n - amount Data]+n*[8bit DATA] + [8bit CRC]*/ /*EXAMPLE for YAT \d(10 10 1 2 3 4 5 6 7 8 9 10 79)*/
  UART4->SR &= ~UART4_SR_RXNE;
  
  /* Read one byte from the receive data register and send it back */
  RXBuffer[RxCounter] = UART4_ReceiveData8();
  
  if(RxCounter==1)//two byte rx is amount byte in package
  {
    AmountByteRX = (0x3F&(RXBuffer[RxCounter]>>2)); 
  }

  RxCounter++;
  
  if(RxCounter == AmountByteRX && RxCounter >=1)
  {
      RxCounter=0;
      flag_package_ready=1;
  }
}



INTERRUPT_HANDLER(ADC1_IRQHandler, 22)
{
        /*clear EOC and rewrite channel. IMPORTANT it need do write BYTE to CSR*/
        ADC1->CSR = ValueClearCSR;
        /* Get converted value scan continuous mode*/
        GetValChannals();
 }

/**
* @brief  GetValChannals.
**/
void GetValChannals(void)
{
        extern ADC ADC_Ch0;
        extern ADC ADC_Ch1;
        extern ADC ADC_Ch2;
        extern ADC ADC_Ch3;
        extern ADC ADC_Ch4;
          
        ADC_Ch0.val= ADC1_GetBufferValue(0);  //zero measuring point 
        ADC_Ch0.flag_update_val=1;
        ADC_Ch1.val= ADC1_GetBufferValue(1);  //battery one measuring point 
        ADC_Ch1.flag_update_val=1;  
        ADC_Ch2.val= ADC1_GetBufferValue(2);  //battery two measuring point 
        ADC_Ch2.flag_update_val=1;
        ADC_Ch3.val= ADC1_GetBufferValue(3);  //battery three measuring point 
        ADC_Ch3.flag_update_val=1;
        ADC_Ch4.val= ADC1_GetBufferValue(4);  //battery four measuring point 
        ADC_Ch4.flag_update_val=1;
}
