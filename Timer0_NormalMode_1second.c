#include "LIB/STD_Type.h"
#include "LIB/BITMATH.h"
#include "LIB/Vect_table.h"
#include "MCAL/TIMER0/TIMER0_interface.h"
#include "MCAL/DIO/DIO_interface.h"
#include "MCAL/ADC/ADC_interface.h"
#include "MCAL/GIE_interrupt/GIE_interface.h"
#include "HAL/LCD_Driver/LCD_interface.h"
#define F_CPU 16000000UL
#include <util/delay.h>

uint16 count=0 ; 

/*
  TIMER_overflow=16US 
  
  DT=100ms 
  
  number=6250

  

 */
int main(void)
{

    DIO_Vid_Set_Pin_Dir(PORTA,PIN0,OUTPUT) ;
    
	   
    while (1) 
    {

		TIM0_Vid_start(_64_prescaling) ;
		TIM0_Vid_OVInterrupt_Enable() ;
			
    }
}

ISR(TIMER0_OF){
	
	count++ ; 
	if(count==97){
		
		DIO_Vid_Set_Pin_Val(PORTA,PIN0,HIGH) ; 
	}
	if(count==194){
		DIO_Vid_Set_Pin_Val(PORTA,PIN0,LOW) ; 
		count=0 ; 
	}
}

ISR(TIMER0_OF){
	
	TCNT0_REG=6;
	count++ ;
	if(count==400)
	{
		DIO_Vid_Toggle_Pin_Val(PORTA,PIN0);
		count=0;
	}
}

