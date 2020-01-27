#include "Check_Tasks.h"

/* Includes ------------------------------------------------------------------*/
#include "Service.h"
#include "ADC.h"
#include "UART.h"
#include "Flash.h"
#include "GPIO.h"
#include "Ring_Buffer.h"
#include "GPIO.h"
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* INIT-----------------------------------------------------------------------*/
extern system_TYPE system;
uint8_t ByteInPackage = 2; //minimal size packege

//volatile uint16_t max_size_TX_include = 0;
void Check_Tasks(void)
{
  extern RING_buffer_t RxRingBuf;
  extern RING_buffer_t TxRingBuf;

  static uint8_t flag_package_ready = 0;
  parsing ParsResult;

// uint8_t GetCountTX = RING_GetCount(&TxRingBuf);
//    if(GetCountTX>0)
//    {/*Enable Interrupt USART Transmit Complete*/

//     /*TEST RING_BUFF_TX_OVERFULL*/
//     uint8_t GetCountTX1 = RING_GetCount(&TxRingBuf);
//     volatile static uint16_t max_size_TX_include = 0;
//     if(GetCountTX1>max_size_TX_include) max_size_TX_include=GetCountTX1;
//     /*TEST RING_BUFF_TX_OVERFULL*/
//      UART4->CR2|=(UART4_SR_TXE);
//    }

//    /*TEST RING_BUFF_RX_OVERFULL*/
//     uint8_t GetCountRX1 = RING_GetCount(&RxRingBuf);
//     volatile static uint16_t max_size_RX_include = 0;
//     if(GetCountRX1>max_size_RX_include) max_size_RX_include=GetCountRX1;
//    /*TEST RING_BUFF_RX_OVERFULL*/

  uint8_t GetCountRX = RING_GetCount(&RxRingBuf);        
  if ((flag_package_ready == 0) && (GetCountRX >= ByteInPackage))
  {
//          /*TEST RING_BUFF_RX_OVERFULL*/
//          volatile static uint16_t max_size_RX_include = 0;
//          if(GetCountRX>max_size_RX_include) max_size_RX_include=GetCountRX;
//          /*TEST RING_BUFF_RX_OVERFULL*/

    ByteInPackage = 0x3F & (RING_ShowSymbol(1, &RxRingBuf) >> 2);
    if (ByteInPackage != 3 && ByteInPackage != 4 && ByteInPackage != 9)
    { /*Check Error*/
      RING_Clear(&RxRingBuf);
      ByteInPackage = 2;
    }
    else
    {
      //          RING_PUSH(1,TxRingBuf)
      //          UART4->CR2|=(UART4_SR_TXE);70% 9 byte package recive
      uint8_t ID = 0x1F & RING_ShowSymbol(0, &RxRingBuf);
      if ((ID != system.ID_MCU) && (ID != ALL_ID))
      { /*retransmission*/

        for (int i = 0; i < ByteInPackage; i++)
        {
                          while( RING_GetCount(&RxRingBuf)==0 )
                          {//wait RxDATA
                            ;
                          }
          RING_PUSH(RxRingBuf.buffer[RxRingBuf.idxOut], TxRingBuf)
          RING_POP_inx(RxRingBuf)
        }
        UART4->CR2|=(UART4_SR_TXE);
        ByteInPackage = 2; //minimal size packege
      }
      else
      { /*For ALL or my ID*/
        if (GetCountRX >= ByteInPackage)
        {
          flag_package_ready = 1;
          ByteInPackage = 2; //minimal size packege
        }
      }
    }
  }

  if (flag_package_ready == 1)
  {
    extern uint8_t flag_wait_command;
    flag_wait_command = 0;
    
//    static uint16_t led_counter=0;
//    led_counter++;
//    if(led_counter>10)
//    {
//      //LED_GPIO_PORT->ODR |= (uint8_t)(LED_GPIO_PINS);
//      testLED();
//      led_counter=0;
//    }
    
    ParsResult = Parsing_RX_Package(&RxRingBuf);
    if (ParsResult.ERROR == 0)
    {                                     /*If CRC was RIGHT, check ID*/
      if (ParsResult.ID == system.ID_MCU) //--------------------------------------------------------------MCU_ID
      {                                   /*If ID was my, execute command*/
        switch (ParsResult.Command)
        {
                        case SEND_MEASUREMENTS:          //test \d(33 12 170) \d(34 12 196)
                          {
                            uint8_t Out_Buffer[10];
                            uint8_t AmountByteTX = pack_DATA_ADC(ParsResult.BuffPackage[0],Out_Buffer);
                            SEND(Out_Buffer, AmountByteTX);
                            break;
                          }
        case BALLANCING_B1: //test  \d(65 12 16)
        {
          GPIO_WriteReverse(BALANCING_1_PORT, BALANCING_1_PIN);
          system.Control.BalancingBattery1 ^= 1;
          break;
        }
        case BALLANCING_B2: //test  \d(97 12 254)
        {
          GPIO_WriteReverse(BALANCING_2_PORT, BALANCING_2_PIN);
          system.Control.BalancingBattery2 ^= 1;
          break;
        }
        case BALLANCING_B3: //test  \d(129 12 100)
        {
          GPIO_WriteReverse(BALANCING_3_PORT, BALANCING_3_PIN);
          system.Control.BalancingBattery3 ^= 1;
          break;
        }
        case BALLANCING_B4: //test  \d(161 12 18)
        {
          GPIO_WriteReverse(BALANCING_4_PORT, BALANCING_4_PIN);
          system.Control.BalancingBattery4 ^= 1;
          break;
        }
        default:
          break;
        }
      }
      if (ParsResult.ID == ALL_ID) //---------------------------------------------------------------------ALL_ID
      {                            /*If ID was common, execute command*/
        switch (ParsResult.Command)
        {
        case SEND_MEASUREMENTS: //test \d(63 12 94)
        {
          uint8_t Out_Buffer[10];
          uint8_t AmountByteTX = pack_DATA_ADC((system.ID_MCU | (0xE0 & ParsResult.BuffPackage[0])), Out_Buffer);
          SEND(Out_Buffer, AmountByteTX);
          SEND(ParsResult.BuffPackage, ParsResult.AmoundByte);
//          /*test*/
//          uint8_t Test_Buffer[3];
//          Test_Buffer[0]=63;
//          Test_Buffer[1]=12;
//          Test_Buffer[2]=94;
//          SEND(Test_Buffer, 3);
//          /*end_test*/
          break;
        }
        case Get_ID: //test \d(127 16 1 156)
        {
          if (ParsResult.BuffPackage[2] > 0 && ParsResult.BuffPackage[2] <= 26)
          {
            system.ID_MCU = ParsResult.BuffPackage[2];
            Write_Adress(ParsResult.BuffPackage[2]);
          }
          else
          {
            /*The address is not in the specified interval [1:26]*/
          }

          ParsResult.BuffPackage[2] += 1;
          ParsResult.BuffPackage[3] = FoundCRC(ParsResult.BuffPackage, 4);

          SEND(ParsResult.BuffPackage, ParsResult.AmoundByte);

          break;
        }
        default:
          break;
        }
      }
      //      if(ParsResult.ID!=ALL_ID && ParsResult.ID!=system.ID_MCU)//------------------------------------Other_ID
      //      {/*If ID was other, pass PACK up*/
      //        for(int i=0; i < ParsResult.AmoundByte;i++)
      //        {
      //          RING_Push(ParsResult.BuffPackage[i], &TxRingBuf);
      //        }
      //      }
    }
    else
    { /*found ERROR in Parsing*/
      // RxCounter=0;//clear counter Reciver
    }
    flag_package_ready = 0;
  }
}

uint8_t pack_DATA_ADC(uint8_t Comand_and_ID, uint8_t *Buf)
{
  extern ADC ADC_Ch0;
  extern ADC ADC_Ch1;
  extern ADC ADC_Ch2;
  extern ADC ADC_Ch3;
  extern ADC ADC_Ch4;

  uint8_t AmountByte = 1 + 7 + 1; //Comand_and_ID(1byte) + AmountByte6bit_DATA50bit(7byte) + CRC(1byte);
  Buf[0] = Comand_and_ID;

  Buf[1] = 0xFC & (AmountByte << 2); //AmountByte in pack

  uint16_t val[5];
  val[0] = ADC_Ch0.valAvg;
  val[1] = ADC_Ch1.valAvg;
  val[2] = ADC_Ch2.valAvg;
  val[3] = ADC_Ch3.valAvg;
  val[4] = ADC_Ch4.valAvg;

  int start_byte = 1;
  int j = 3, k = 0;            //j-varible ofset; k - varible byte in RXBuffer
  for (int i = 0; i <= 4; i++) //i-10bit information
  {
    if (j % 4 == 0) //in 5byte include 4channels->cycle
    {
      if (i != 0)
        k++;
      Buf[start_byte + k] = 0;
      j = 0;
    }
    Buf[start_byte + k] |= (uint8_t)(0xFF & val[i] >> (2 + 2 * j)); //HighREG
    Buf[start_byte + k + 1] = 0;
    Buf[start_byte + k + 1] |= (uint8_t)(0xFF & val[i] << (6 - 2 * j)); //LowREG
    j++;
    k++;
  }
  Buf[AmountByte - 1] = FoundCRC(Buf, AmountByte);

  return AmountByte;
}

parsing Parsing_RX_Package(RING_buffer_t *Buff)
{
  parsing ParsResult;

  ParsResult.BuffPackage[0] = RING_Pop(Buff);
  ParsResult.BuffPackage[1] = RING_Pop(Buff);
  ParsResult.Command = (ParsResult.BuffPackage[0] >> 5) & 0x7;
  ParsResult.ID = ParsResult.BuffPackage[0] & 0x1F;
  ParsResult.AmoundByte = 0x3F & (ParsResult.BuffPackage[1] >> 2);
  for (int i = 2; i < ParsResult.AmoundByte; i++)
  {
    while( RING_GetCount(&RxRingBuf)==0 )
                         {//wait RxDATA
                           ;
                         }
    ParsResult.BuffPackage[i] = RING_Pop(Buff);
  }

  ParsResult.ERROR = 0;
  uint8_t CRC = 0;
  CRC = FoundCRC(ParsResult.BuffPackage, ParsResult.AmoundByte);

  if (CRC != ParsResult.BuffPackage[ParsResult.AmoundByte - 1])
  {
    ParsResult.ERROR |= ERROR_CRC;
  }

  return ParsResult;
}

uint8_t FoundCRC(uint8_t *Buff, uint8_t AmoundByte)
{
  uint16_t CRC = 0;

  for (int i = 0; i < (AmoundByte - 1); i++)
  {
    CRC += Buff[i] * 44111;
  }
  CRC = (CRC ^ (CRC >> 8));
  return (uint8_t)CRC;
}