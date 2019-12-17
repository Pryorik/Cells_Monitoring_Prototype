#include "Check_Tasks.h"

/* Includes ------------------------------------------------------------------*/
#include "Service.h"
#include "ADC.h"
#include "UART.h"

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* INIT-----------------------------------------------------------------------*/
extern system_TYPE system;

void Check_Tasks(void)
{
  extern uint8_t AmountByteRX;
  extern uint8_t AmountByteTX;
  extern uint8_t flag_package_ready;
  extern uint8_t RXBuffer[];
  extern uint8_t *TXBuff_ptr;
  extern uint8_t RxCounter;
    
  parsing ParsResult; 
  static uint8_t TXBuffer[20];//1ComADD+Am+DATA7+1CRS = 9 + spare 11byte
  
  if(flag_package_ready)
  {
      ParsResult = Parsing_RX_Package();
      if(ParsResult.ERROR==0)
      {/*If CRC was RIGHT, check ID*/
          if(ParsResult.ID==system.ID_MCU)//----------------------------------------------MCU_ID
          {/*If ID was my, execute command*/
                  switch(ParsResult.Command)
                  {
                    case SEND_MEASUREMENTS:          //test \d(33 12 170)
                      {
                        AmountByteTX = pack_DATA_ADC( RXBuffer[0],TXBuffer );
                        TXBuff_ptr   = &TXBuffer[0];
                        UART4_ITConfig(UART4_IT_TXE, ENABLE);               
                        break;
                      }
                    default:
                      break;
                  }
          }
          else
          {
                if(ParsResult.ID==ALL_ID)//----------------------------------------------ALL_ID
                {/*If ID was common, execute command*/
                      switch(ParsResult.Command)
                      {
                        case SEND_MEASUREMENTS:          //test \d(63 12 94)
                          {
                            AmountByteTX = pack_DATA_ADC((ParsResult.ID|(0XE0&RXBuffer[0])),TXBuffer);
                            TXBuff_ptr   = &TXBuffer[0];
                            UART4_ITConfig(UART4_IT_TXE, ENABLE);  
                            
                            while( (UART4->CR2 & UART4_CR2_TIEN) != 0 )//if UARTinterrupt_off (UART_DR empty) 
                            {
                              ;
                            }
                            TXBuffer[0] = (uint8_t)ALL_ID|((uint8_t)SEND_MEASUREMENTS<<5);                           
                            TXBuffer[1] = 3<<2;
                            TXBuffer[2] = FoundCRC(TXBuffer,3); 
                            AmountByteTX = 3;
                            TXBuff_ptr   = &TXBuffer[0];
                            UART4_ITConfig(UART4_IT_TXE, ENABLE);  
                            break;
                          }
                        default:
                          break;
                      }
                }
                else//-------------------------------------------------------------------Other_ID
                {/*If ID was other, pass PACK up*/
                  AmountByteTX=AmountByteRX;
                  TXBuff_ptr  = &RXBuffer[0];
                  UART4_ITConfig(UART4_IT_TXE, ENABLE);//test \d(35 12 35)
                }
          }
      }
      else
      {/*found ERROR in Parsing*/
       // RxCounter=0;//clear counter Reciver
      }
      flag_package_ready=0;
  }
}

uint8_t pack_DATA_ADC(uint8_t Comand_and_ID, uint8_t *Buf)
{
      extern ADC ADC_Ch0;
      extern ADC ADC_Ch1;
      extern ADC ADC_Ch2;
      extern ADC ADC_Ch3;
      extern ADC ADC_Ch4;
      
      uint8_t AmountByteTX;
  
      AmountByteTX=1+7+1;//Comand_and_ID(1byte) + AmountByte6bit_DATA50bit(7byte) + CRC(1byte)
      
      Buf[0]=Comand_and_ID;
      
      Buf[1]=0;
      Buf[1] = 0xFC&(AmountByteTX<<2);//AmountByte in pack
      
      uint16_t val[5];
      val[0] = ADC_Ch0.valAvg;
      val[1] = ADC_Ch1.valAvg;
      val[2] = ADC_Ch2.valAvg;
      val[3] = ADC_Ch3.valAvg;
      val[4] = ADC_Ch4.valAvg;
      
      int start_byte = 1;
      int j=3,k=0; //j-varible ofset; k - varible byte in RXBuffer
      for(int i=0;i<=4;i++) //i-10bit information
      {
            if(j%4==0)//in 5byte include 4channels->cycle
            {
                  if(i!=0)k++;
                  Buf[start_byte+k] = 0;
                  j=0;
            }
            Buf[start_byte+k]   |= (uint8_t)(0xFF & val[i] >> (2+2*j));   //HighREG
            Buf[start_byte+k+1]  = 0;
            Buf[start_byte+k+1] |= (uint8_t)(0xFF & val[i] << (6-2*j));   //LowREG
            j++;
            k++;
      }
      Buf[AmountByteTX-1] = FoundCRC(Buf,AmountByteTX); 
      
      return AmountByteTX;
}

parsing Parsing_RX_Package(void)
{
  extern uint8_t RXBuffer[];
  extern uint8_t AmountByteRX;
  parsing ParsResult; 
  
  ParsResult.Command = (RXBuffer[0]>>5) & 0x7;
  ParsResult.ID = RXBuffer[0] & 0x1F;
  ParsResult.ERROR=0;
  
  uint8_t CRC=0;
  CRC = FoundCRC(RXBuffer, AmountByteRX);
  
  if(CRC != RXBuffer[AmountByteRX-1] )
  {
      ParsResult.ERROR|=ERROR_CRC;
  }
  
  if(ParsResult.ID == system.ID_MCU && AmountByteRX>3)
  {
      ParsResult.ERROR|=ERROR_AmountByteInCommand;
  }
  return ParsResult;
}

uint8_t FoundCRC(uint8_t *Buff, uint8_t amountByte)
{
  uint16_t CRC=0;
    for(int i=0; i<(amountByte-1);i++)
  {
      CRC+= Buff[i]*44111;
      
  }
  CRC = CRC ^ (CRC >> 8); 
  return CRC = CRC & 0xFF;
}