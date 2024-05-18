#include "STD_Type.h"
#include "BITMATH.h"
#include "DIO_interface.h"
#include "UART_Interface.h"
#include "SPI_interface.h"
#include "LCD_interface.h"
#include "I2C_interface.h"
#include "GIE_interface.h"
#define F_CPU 16000000UL
#include "util/delay.h"
u8 val=0;
int main(void)
{
	
	DIO_Vid_Set_Pin_Dir(PORTD,PIN7,OUTPUT);
	
	while(1)
	{
		I2C_Slave_INIT(2);
		I2C_Check_Slave_Add_WR_REQ();
		val=I2C_Slave_Read_Byte();
		if(val==5)
		{
			DIO_Vid_Set_Pin_Val(PORTD,PIN7,HIGH);
		}
		else
		{
			DIO_Vid_Set_Pin_Val(PORTD,PIN7,LOW);

		}

		
	}
}

