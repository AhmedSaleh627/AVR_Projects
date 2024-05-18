/*
 * SW_ICU.c
 *
 * Created: 06/10/2023 17:18:02
 * Author : AMIT
 */ 

#include "BIT_MATH.h" 
#include "STD_TYPE.h" 
#include "DIO_interface.h" 
#include "TIMER0_interface.h" 
#include "TIMER1_interface.h" 
#include "EXIT_interface.h" 
#include "LCD_config.h" 
#include "LCD_interface.h" 
#include "GIE_interface.h"
#define  F_CPU 16000000UL 
#include "util/delay.h"
volatile static u32 overflow_ticks=0 ; 

volatile static u32 on_ticks=0 ; 
void  SW_ICU(void) ; 
int main(void)
{  
      /*  Lcd pin init*/
	  /* PORT DIR */
	  DIO_Vid_Set_Port_Dir(LCD_DPORT,0xf0) ;
	  DIO_Vid_Set_Pin_Dir(LCD_CPORT,LCD_RS_PIN,OUTPUT) ;
	  DIO_Vid_Set_Pin_Dir(LCD_CPORT,LCD_RW_PIN,OUTPUT) ;
	  DIO_Vid_Set_Pin_Dir(LCD_CPORT,LCD_EN_PIN,OUTPUT) ;
	  
	
	  DIO_Vid_Set_Pin_Dir(PORTD,PIN2,INPUT) ; 
	  DIO_Vid_Set_Pin_Dir(PORTB,PIN3,OUTPUT) ; 
	  LCD_Vid_Init() ;
	     
		
		  TIMER1_Vid_NormalMode_Init() ; 
		 
              /* enable global interrupt */
              GIE_Vid_Enable();
                 EXT_Vid_Interrupt_Init(RISING_EDGE) ;
                 EXT_Vid_Interrupt0() ;
              EXT_Vid_Set_CallBack(SW_ICU) ; 
   
    while (1) 
   {
	   
		TIM0_Vid_Fast_PWM(20) ; 
		LCD_Vid_GOTOXY(0,0) ; 
		LCD_Vid_Send_number( overflow_ticks) ; 
		_delay_ms(50) ; 
		LCD_Vid_GOTOXY(0,1) ; 
		LCD_Vid_Send_number(on_ticks) ;
		_delay_ms(50) ;  
    }
}

void  SW_ICU(void){

  static u8 count=0 ;  
   count ++ ; 
   
   if(count==1){
	   TIMER1_Vid_RestTimer() ; 
	   EXT_Vid_Interrupt_Init(FALLING_EDGE) ;
	   
   }
   if(count==2){
on_ticks=TIMER1_u16_Read_TimerVal() ; 
  
    EXT_Vid_Interrupt_Init(RISING_EDGE) ;
  
   }
	if(count==3){
	
	  overflow_ticks=TIMER1_u16_Read_TimerVal(); 

  	}
	
	
	
}