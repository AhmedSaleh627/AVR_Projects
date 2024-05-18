#include "LIB/STD_Type.h"
#include "LIB/BITMATH.h"
#include "MCAL/DIO/DIO_interface.h"
#include "HAL/LCD_Driver/LCD_interface.h"
#include "MCAL/SPI/SPI_interface.h"
#include "HAL/KeyPad/Keypad_interface.h"
#include "MCAL/ADC/ADC_interface.h"
#include "MCAL/GIE_interrupt/GIE_interface.h"
#define F_CPU 16000000UL
#include "util/delay.h"

uint16 val=0;
 uint16 analogval=0;
 uint16 val2=0;
uint16 analogval2=0;
u8 val_asc=0;
u8 val_asc_l=0;
u8 val_asc_r=0;
u8 val_l=0;
u8 val_r=0;
u8 pass=0;

void TEMP_SENSOR()
{
	analogval=val*500/1024;
	val_asc=int_to_asc(analogval);
	val_l=analogval/10;
	val_r=analogval%10;
	val_asc_l=int_to_asc(val_l);
	val_asc_r=int_to_asc(val_r);
	
	DIO_Vid_Set_Pin_Val(PORTB,PIN4,LOW);

		SPI_Vid_Master_Send(val_asc_l);
		_delay_ms(300);
		SPI_Vid_Master_Send(val_asc_r);
		_delay_ms(300);
		

	
	DIO_Vid_Set_Pin_Val(PORTB,PIN4,HIGH);
	_delay_ms(400);
	
}

void LDR_Sensor()
{
	val2=(val2 *5)/1024;

	if(val2>3)
	{
		DIO_Vid_Set_Pin_Val(PORTC,PIN0,HIGH);
	}
	else
	{
		DIO_Vid_Set_Pin_Val(PORTC,PIN0,LOW);

	}

}





int main(void)
{
	
	DIO_Vid_Set_Pin_Dir(PORTB,PIN5,OUTPUT);
	DIO_Vid_Set_Pin_Dir(PORTB,PIN7,OUTPUT);
	DIO_Vid_Set_Pin_Dir(PORTD,PIN7,OUTPUT);
	DIO_Vid_Set_Pin_Dir(PORTB,PIN4,OUTPUT);
	DIO_Vid_Set_Pin_Dir(PORTB,PIN6,INPUT);
	DIO_Vid_Set_Pin_Dir(PORTD,PIN0,OUTPUT);
	DIO_Vid_Set_Pin_Dir(PORTC,PIN0,OUTPUT);
	SPI_Vid_Master_Init();
	ADC_Vid_Init() ;
	GIE_Vid_Enable();
	ADC_EnableInt();
	DIO_Vid_Set_Pin_Val(PORTA,PIN0,INPUT);
	while (1)
	{
	
		val2=ADC_u16_Read(ADC_Channel_0) ;
		ADC_Vid_Set_CallBack(LDR_Sensor);
		val=ADC_u16_Read(ADC_Channel_1) ;
		ADC_Vid_Set_CallBack(TEMP_SENSOR);
		
		
		

	



	}

	
}

