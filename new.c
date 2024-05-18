#include "LIB/STD_Type.h"
#include "LIB/BITMATH.h"
#include "MCAL/DIO/DIO_interface.h"
#include "MCAL/GIE_interrupt/GIE_interface.h"
#include "MCAL/TIMER0/TIMER0_private.h"
#include "MCAL/TIMER0/TIMER0_interface.h"
#include "HAL/DC_Motor_Driver/DC_Motor_interface.h"

#include "LIB/Vect_table.h"
#define F_CPU 16000000UL
#include "util/delay.h"

volatile u32 SW_Counter1 =0;
volatile u32 SW_Counter2 =0;
void B_TOG()
{
	// 5 seconds if using 1024 prescaler if using 64 prescaler values will be 4882 and 9765
	SW_Counter1++ ;
	if(SW_Counter1==305){
		
		DIO_Vid_Toggle_Pin_Val(PORTD,PIN1);
	}
	if(SW_Counter1==610){
		DIO_Vid_Toggle_Pin_Val(PORTD,PIN1);
		SW_Counter1=0 ;
	}
}


void LED_TOGGLE(void)
{

	SW_Counter2++ ;
	if (SW_Counter2==2000)
	{
		DIO_Vid_Toggle_Pin_Val(PORTD,PIN0);
		SW_Counter2=0;
	}
}


int main(void)
{
	TIM0_Vid_start(_64_prescaling);
	TIM0_Vid_CTC_Init();
	//TIM0_Vid_OVInterrupt_Enable();
	DIO_Vid_Set_Pin_Dir(PORTD,PIN0,OUTPUT);
	DIO_Vid_Set_Pin_Dir(PORTD,PIN1,OUTPUT);
	TIM0_Vid_SetCallBack(CTC_MODE,LED_TOGGLE);
	//TIM0_Vid_SetCallBack(OVI_MODE,B_TOG);
	GIE_Vid_Enable();
	
	while(1)
	{
		
		
	}

	
	
}


