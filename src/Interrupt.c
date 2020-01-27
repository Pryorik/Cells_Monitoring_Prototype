
/* Includes ------------------------------------------------------------------*/
#include "Interrupt.h"
#include "service.h"
#include "stm8s_uart4.h"
#include "stm8s_adc1.h"
#include "Check_Tasks.h"
#include "Ring_Buffer.h"
#include "Tests.h"
/* Private define ------------------------------------------------------------*/
#define RX_BUFFER_SIZE 40 //1ComADD+Am+DATA7+1CRS = 9 + spare 11byte
#define TX_BUFFER_SIZE 40 
/* Private macro -------------------------------------------------------------*/

/* variables ---------------------------------------------------------*/
uint8_t RXBuffer[RX_BUFFER_SIZE];
uint8_t TXBuffer[TX_BUFFER_SIZE];
RING_buffer_t TxRingBuf = {.buffer = TXBuffer, .size = TX_BUFFER_SIZE};
RING_buffer_t RxRingBuf = {.buffer = RXBuffer, .size = RX_BUFFER_SIZE};
extern system_TYPE system;

/**
  * @brief  Timer5 Update/Overflow/Break/Trigger Interrupt routine
  * @param  None
  * @retval None
  */
 uint8_t flag_wait_command=0;
 extern RING_buffer_t RxRingBuf; 
 INTERRUPT_HANDLER(TIM5_UPD_OVF_BRK_TRG_IRQHandler, 13)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
  TIM5->SR1 &= (~TIM5_SR1_UIF);
  Check_Tasks();
//  if(flag_wait_command==1)
//  {
//      //wfi(); 
//      RING_Clear(&RxRingBuf);
//      uint8_t ByteInPackage = 2;//minimal size packege
//  }
//  flag_wait_command=1;
}

INTERRUPT_HANDLER(UART4_TX_IRQHandler, 17)
{   
    /* Write one byte to the transmit data register */
    UART4->DR = RING_Pop(&TxRingBuf);
    
    /*software clear TXEmpty*/
    UART4->SR &= ~UART4_SR_TXE;
    
    if(RING_GetCount(&TxRingBuf) == 0)
    {/* Disable the USART Transmit Complete interrupt */
        UART4->CR2&=(~UART4_SR_TXE);//UART4_ITConfig(UART4_IT_TXE, DISABLE); 
    }
}

INTERRUPT_HANDLER(UART4_RX_IRQHandler, 18)
{
/*[3bitCommand+5bitAddr]+[6bitAmountData+2bitDATA]+n*[8bit DATA] + [8bit CRC]*/ 
  
  UART4->SR &= ~UART4_SR_RXNE; 
  RING_PUSH(UART4->DR, RxRingBuf)
  flag_wait_command=0;
}

uint32_t ValueClearCSR=0x20+ADC1_CHANNEL_4;
INTERRUPT_HANDLER(ADC1_IRQHandler, 22)
{
        static uint8_t counter_devided=0;
        
        /*clear EOC and rewrite channel. IMPORTANT it need do write BYTE to CSR*/
        ADC1->CSR = ValueClearCSR;
        /* Get converted value scan continuous mode*/
        if(counter_devided==0) 
        {
          GetValChannals();
        }
        counter_devided++;
        if(counter_devided==5) counter_devided=0;
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
